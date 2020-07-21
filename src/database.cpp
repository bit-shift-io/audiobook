
#include <QSqlDatabase>
#include <QSqlDriver>
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
    QSqlDatabase libraryDatabase = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), dbName);

    if (!dbFileName.isEmpty()) {
        // load from file
        libraryDatabase.setDatabaseName(QStringLiteral("file:") + dbFileName);
    } else {
        // from memory
        libraryDatabase.setDatabaseName(QStringLiteral("file:memdb1?mode=memory"));
    }

    // db options
    libraryDatabase.setConnectOptions(QStringLiteral("foreign_keys = ON;locking_mode = EXCLUSIVE;QSQLITE_OPEN_URI;QSQLITE_BUSY_TIMEOUT=500000"));

    // open
    auto result = libraryDatabase.open();
    if (result) {
        qDebug() << "database open";
    } else {
        qDebug() << "database not open";
    }

    qDebug() << "Database::init" << (libraryDatabase.driver()->hasFeature(QSqlDriver::Transactions) ? "yes" : "no");

    //libraryDatabase.exec(QStringLiteral("PRAGMA foreign_keys = ON;"));

    //d = std::make_unique<DatabaseInterfacePrivate>(tracksDatabase);

    initDatabase();
    initRequest();

    if (!dbFileName.isEmpty()) {
        reloadExistingDatabase();
    }
}

void Database::initDatabase()
{

}

void Database::initRequest()
{

}

void Database::reloadExistingDatabase()
{

}
