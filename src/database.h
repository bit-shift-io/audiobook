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
    void setInfo(const QString &xKey, const QString &xValue);
    QVariant getInfo(const QString &xKey);
    void setChapter(const Chapter &xChapter);
    const Chapter getChapter(const QString &xPath);

signals:

private:
    QSqlDatabase mDatabase;

};

#endif // DATABASE_H
