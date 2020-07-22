#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include "book.h"

class QSqlDatabase;

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);
    ~Database() override;

    // init database
    Q_INVOKABLE void init(const QString &dbName, const QString &dbFileName = {});
    void initDatabase();
    void initRequest();
    void reloadExistingDatabase();
    void addFileInfo(const QString xPath, const int xFileSize, const int xDuration, const QString xArtist, const QString xYear);


signals:

private:
    QSqlDatabase *mDatabase = nullptr;

};

#endif // DATABASE_H
