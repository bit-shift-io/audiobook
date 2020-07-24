#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include "book.h"

class QQmlEngine;
class QJSEngine;

class Database : public QObject
{
    Q_OBJECT
    const static int DB_VERSION = 0;

public:
    Database(const Database&) = delete; // disable copy for singleton
    static Database *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    ~Database() override;

    void initDatabase();

    void setInfo(const QString &xKey, const QString &xValue);

    QVariant getInfo(const QString &xKey);
    void setChapter(const Chapter &xChapter);
    const Chapter getChapter(const QString &xPath);

    void setBook(const Book &xBook);
    const Book getBook(const QString &xPath);

signals:

private:
    explicit Database(QObject *parent = nullptr);

    QSqlDatabase mDatabase;

};

#endif // DATABASE_H
