

#include <QSqlDriver>
#include <QSqlQuery>
#include <QDebug>
#include "database.h"
#include "util.h"


Database::Database(QObject *parent)
    : QObject(parent)
{
    QString database_path = Util::getAppConfigLocation() + "library.db";
    QString database_name("Library");

    mDatabase = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), database_name);

    if (!database_path.isEmpty()) {
        // load from file
        mDatabase.setDatabaseName(QStringLiteral("file:") + database_path);
    } else {
        // from memory
        mDatabase.setDatabaseName(QStringLiteral("file:memdb1?mode=memory"));
    }

    // db options
    mDatabase.setConnectOptions(QStringLiteral("foreign_keys = ON;locking_mode = EXCLUSIVE;QSQLITE_OPEN_URI;QSQLITE_BUSY_TIMEOUT=500000"));

    // open
    auto result = mDatabase.open();
    if (!result) {
        qDebug() << "database not open";
    }

    // create db or load
    initDatabase();

    if (!database_path.isEmpty()) {
        qDebug() << "database is here!";
        //reloadExistingDatabase();
    }
}

Database::~Database()
{
    if (mDatabase.isOpen())
        mDatabase.close();
}


void Database::initDatabase()
{
    QStringList tables = mDatabase.tables();
    QSqlQuery query;

    // check if database contains data
    if (tables.contains("info", Qt::CaseInsensitive) && tables.contains("files", Qt::CaseInsensitive)) {
        if (query.exec("SELECT * FROM info WHERE key = 'db_version'")) {
            query.next(); // get result
            int version = query.value("value").toInt();
            if (version == DB_VERSION)
                return;
        }
    }

    // create info table
    query.exec("create table info "
        "(key text primary key, "
        "string text, "
        "value integer)");

    // db version
    query.prepare("INSERT INTO info (key, value) VALUES (?, ?)");
    query.addBindValue("db_version");
    query.addBindValue(DB_VERSION);
    query.exec();

    // create files table
    query.exec("create table files "
        "(path text primary key, "
        "title text, "
        "duration integer, "
        "artist text, "
        "size integer, "
        "year integer)");
}



void Database::addChapter(const Chapter xChapter)
{
    QSqlQuery query;
    query.prepare("INSERT INTO files (path, size, duration, artist, genre, year) VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(xChapter.filePath);
    query.addBindValue(xChapter.size);
    query.addBindValue(xChapter.duration);
    query.addBindValue(xChapter.artist);
    query.addBindValue(xChapter.genre);
    query.addBindValue(xChapter.year);
    query.exec();
}



