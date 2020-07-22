#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include "book.h"


class Database : public QObject
{
    Q_OBJECT
    const static int DB_VERSION = 1;

public:
    explicit Database(QObject *parent = nullptr);
    ~Database() override;

    // init database
    void initDatabase();
    void addChapter(const Chapter xChapter);

signals:

private:
    QSqlDatabase mDatabase;

};

#endif // DATABASE_H
