

#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "database.h"
#include "util.h"
#include "settings.h"


Database::Database(QObject *parent)
    : QObject(parent)
{
    // Library path from settings
    mLibraryPath = Settings::value("library_path", Util::getMusicLocation()).toString();

    QString database_path = Util::getAppConfigLocation() + "/library.db";
    QString database_name("Library");
    qDebug() << database_path;
    mDatabase = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), database_name);
    mDatabase.setDatabaseName(QStringLiteral("file:") + database_path);
    mDatabase.setConnectOptions(QStringLiteral("foreign_keys = ON;locking_mode = EXCLUSIVE;QSQLITE_OPEN_URI;QSQLITE_BUSY_TIMEOUT=500000"));

    // open
    auto result = mDatabase.open();
    if (!result) {
        qDebug() << "database not open";
    }

    // create db or load
    initDatabase();

    // nothing in library, rescan
    if (isEmpty())
        updateLibrary();
}

Database *Database::instance()
{
    static Database* instance = new Database;
    return instance;
}

QObject *Database::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return Database::instance(); // C++ and QML instance
}

Database::~Database()
{
    if (mDatabase.isOpen())
        mDatabase.close();
}


QStringList Database::getBookDirs()
{
    QStringList result;

    // loop dirs
    QDir lib_dir(mLibraryPath);
    QDirIterator directories(mLibraryPath, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

    while(directories.hasNext()) {
        directories.next();

        // does folder contain any audio files? if we have audio files, this is a book
        QDir current_dir(directories.filePath());
        QStringList dir_list = current_dir.entryList(mFileFilters, QDir::NoDotAndDotDot | QDir::Files);
        if (dir_list.count() == 0)
            continue;

        result.append(directories.filePath().replace(mLibraryPath, ""));
    }

    return result;
}


QStringList Database::getBookFiles(const QString &xPath)
{
    QDir current_dir(xPath);
    return current_dir.entryList(mFileFilters, QDir::NoDotAndDotDot | QDir::Files);
}


void Database::initDatabase()
{
    QStringList tables = mDatabase.tables();
    QSqlQuery query(mDatabase);

    // check if database contains data
    if (tables.contains("info", Qt::CaseInsensitive)
        && tables.contains("files", Qt::CaseInsensitive)
        && getInfo("db_version").toInt() == DB_VERSION) {
            return;
    }

    qDebug() << "creating db";

    // drop old table data
    query.exec("DROP TABLE info");
    query.exec("DROP TABLE files");

    // create info table
    query.exec("create table info "
        "(key text primary key, "
        "value string)");

    // db version
    setInfo("db_version", QString::number(DB_VERSION));
    //addInfo("library_path", Library::instance()->path()); // done in library update

    // create files table
    query.exec("create table files "
        "(path text primary key, "
        "title text, "
        "duration integer, "
        "artist text, "
        "genre text, "
        "year integer)");

    // create books table
    query.exec("create table books "
        "(path text primary key, "
        "progress integer)");
}


void Database::setInfo(const QString &xKey, const QString &xValue)
{
    QSqlQuery query(mDatabase);
    query.prepare("REPLACE INTO info (key, value) VALUES (?, ?)");
    query.addBindValue(xKey);
    query.addBindValue(xValue);
    if(!query.exec()) {
        qDebug() << "error adding info" << mDatabase.lastError().text();
    }
}


QVariant Database::getInfo(const QString &xKey)
{
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM info WHERE key = ?");
    query.addBindValue(xKey);

    if (query.exec()) {
        while (query.next()) // get first result
            return query.value("value");
    }

    qDebug() << "error getting info" << mDatabase.lastError().text();
    return QVariant();
}



void Database::writeChapter(const Chapter &xChapter)
{
    QSqlQuery query(mDatabase);
    query.prepare("REPLACE INTO files (path, title, duration, artist, genre, year) VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(xChapter.path);
    query.addBindValue(xChapter.title);
    query.addBindValue(xChapter.duration);
    query.addBindValue(xChapter.artist);
    query.addBindValue(xChapter.genre);
    query.addBindValue(xChapter.year);
    if(!query.exec()) {
        qDebug() << "error adding chapter" << mDatabase.lastError().text();
    }
}

Chapter Database::getChapter(const QString &xPath)
{
    Chapter c;
    c.path = xPath;

    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM files WHERE path = ?");
    query.addBindValue(xPath);

    if (query.exec()) {
        // from db
        while (query.next()) { // get first result
            c.title = query.value("title").toString();
            c.duration = query.value("duration").toInt();
            c.artist = query.value("artist").toString();
            c.genre = query.value("genre").toString();
            c.year = query.value("year").toInt();
        }
    }

    if (c.isEmpty()) {
        // from file
        QString abs_path = mLibraryPath + xPath;
        QFileInfo file_info = QFileInfo(abs_path);

        c.duration = Util::getTimeMSec(abs_path);
        c.artist = Util::getTagArtist(abs_path);
        c.genre = Util::getTagGenre(abs_path);
        c.title = Util::getTagTitle(abs_path);
        c.year = Util::getTagYear(abs_path);

        if (c.title.isEmpty())
            c.title = Util::toCamelCase(file_info.baseName().replace("_", " "));

        if (c.year == -1)
            c.year = file_info.birthTime().date().year();

        writeChapter(c);
    }

    return c;
}


void Database::writeBook(const Book &xBook)
{
    QSqlQuery query(mDatabase);
    query.prepare("REPLACE INTO books (path, progress) VALUES (?, ?)");
    query.addBindValue(xBook.path);
    query.addBindValue(xBook.progress);
    if(!query.exec()) {
        qDebug() << "error adding book" << mDatabase.lastError().text();
    }
}


Book Database::getBook(const QString &xPath)
{
    Book b;
    b.path = xPath;

    QSqlQuery query(mDatabase);

    // get book info
    query.prepare("SELECT * FROM books WHERE path = ?");
    query.addBindValue(xPath);

    if (query.exec()) {
        // from db
        while (query.next()) { // get first result
            b.progress = query.value("progress").toInt();
        }
    }

    // get chapter files
    query = QSqlQuery(mDatabase);
    QString q = QString("SELECT * FROM files WHERE path LIKE '%1/%'").arg(xPath);
    query.prepare(q); // Note: binds are broken here, so use string arg

    if (query.exec()) {
        while (query.next()) { // get first result
            Chapter c;
            c.path = query.value("path").toString();
            c.title = query.value("title").toString();
            c.duration = query.value("duration").toInt();
            c.artist = query.value("artist").toString();
            c.genre = query.value("genre").toString();
            c.year = query.value("year").toInt();
            b.addChapter(c);
        }
    }

    if (b.isEmpty()) {
        // from file
        QStringList chapter_files = getBookFiles(mLibraryPath + xPath);

        for (QString current_file : chapter_files) {
            QString chapter_path = xPath + "/" + current_file;
            Chapter c = getChapter(chapter_path);
            b.addChapter(c);
        }

        writeBook(b);
    }

    b.ready();
    return b;
}



QString Database::libraryPath() const
{
    return mLibraryPath;
}


void Database::setLibraryPath(QString &xPath) {
    xPath = xPath.replace("file://","");
    if (xPath == mLibraryPath)
        return;
    mLibraryPath = xPath;
    Settings::setValue("library_path", mLibraryPath);
    qDebug() << mLibraryPath;
    updateLibrary();
    emit pathChanged();
}


int Database::size() const
{
    return mLibraryItems.size();
}


bool Database::isEmpty() const
{
    return mLibraryItems.isEmpty();
}


QVector<Book> Database::getLibraryItems() {
    return mLibraryItems;
}


Book * Database::getLibraryItem(QString &xPath)
{
    for(Book &b: mLibraryItems) {
        if (b.path == xPath)
            return &b;
    }
    return nullptr;
}


bool caseInsensitiveLessThan(const Book &s1, const Book &s2) {
    return s1.title.toLower() < s2.title.toLower();
}


void Database::updateLibrary() {
    // delete old books
    mLibraryItems = QVector<Book>();

    // set library path
    setInfo("library_path", mLibraryPath);

    // get book directories
    QStringList book_dirs = getBookDirs();
    for (QString book_path : book_dirs) {
        Book book = getBook(book_path);
        mLibraryItems.append(book);
    }

    // sort
    qSort(mLibraryItems.begin(), mLibraryItems.end(), caseInsensitiveLessThan);

    emit libraryUpdated();
}

