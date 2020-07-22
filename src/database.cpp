
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QDebug>
#include "database.h"


Database::Database(QObject *parent)
    : QObject(parent)
{

}

Database::~Database()
{

}

void Database::init(const QString &dbName, const QString &dbFileName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), dbName);

    if (!dbFileName.isEmpty()) {
        // load from file
        db.setDatabaseName(QStringLiteral("file:") + dbFileName);
    } else {
        // from memory
        db.setDatabaseName(QStringLiteral("file:memdb1?mode=memory"));
    }

    // db options
    db.setConnectOptions(QStringLiteral("foreign_keys = ON;locking_mode = EXCLUSIVE;QSQLITE_OPEN_URI;QSQLITE_BUSY_TIMEOUT=500000"));

    // open
    auto result = db.open();
    if (result) {
        qDebug() << "database open";
    } else {
        qDebug() << "database not open";
    }

    qDebug() << "Database::init" << (db.driver()->hasFeature(QSqlDriver::Transactions) ? "yes" : "no");

    //libraryDatabase.exec(QStringLiteral("PRAGMA foreign_keys = ON;"));

    mDatabase = &db;

    initDatabase();
    initRequest();

    if (!dbFileName.isEmpty()) {
        reloadExistingDatabase();
    }
}

void Database::initDatabase()
{
    QStringList tables = mDatabase->tables();

    // check if database contains data
    if (tables.contains("info", Qt::CaseInsensitive)
            && tables.contains("files", Qt::CaseInsensitive))
            return;

    // create info table

    // create files table


}

void Database::initRequest()
{
    QSqlQuery query("SELECT * FROM files");
}

void Database::reloadExistingDatabase()
{

}

void Database::addFileInfo(const QString xPath, const int xFileSize, const int xDuration, const QString xArtist, const QString xYear)
{
    QSqlQuery query;
    query.prepare("INSERT INTO files (path, size, duration, artist, year) VALUES (?, ?, ?)");
    query.addBindValue(xPath);
    query.addBindValue(xFileSize);
    query.addBindValue(xDuration);
    query.addBindValue(xArtist);
    query.addBindValue(xYear);
    query.exec();
}



