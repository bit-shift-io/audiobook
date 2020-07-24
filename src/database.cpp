

#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "library.h"
#include "database.h"
#include "util.h"


Database::Database(QObject *parent)
    : QObject(parent)
{
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



void Database::setChapter(const Chapter &xChapter)
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

const Chapter Database::getChapter(const QString &xPath)
{
    Chapter c;
    c.path = xPath;

    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM files WHERE path = ?");
    query.addBindValue(xPath);

    if (query.exec()) {
        while (query.next()) { // get first result
            c.title = query.value("title").toString();
            c.duration = query.value("duration").toInt();
            c.artist = query.value("artist").toString();
            c.genre = query.value("genre").toString();
            c.year = query.value("year").toInt();
        }
    }

    return c;
}


void Database::setBook(const Book &xBook)
{
    QSqlQuery query(mDatabase);
    query.prepare("REPLACE INTO books (path, progress) VALUES (?, ?)");
    query.addBindValue(xBook.path);
    query.addBindValue(xBook.progress);
    if(!query.exec()) {
        qDebug() << "error adding book" << mDatabase.lastError().text();
    }
}


const Book Database::getBook(const QString &xPath)
{
    Book b;
    b.path = xPath;

    QSqlQuery query(mDatabase);

    // get books
    query.prepare("SELECT * FROM books WHERE path = ?");
    query.addBindValue(xPath);

    if (query.exec()) {
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

    return b;
}



