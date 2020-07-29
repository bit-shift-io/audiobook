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
    const static int DB_VERSION = 1;

    Q_PROPERTY(QString libraryPath READ libraryPath WRITE setLibraryPath NOTIFY pathChanged)
    Q_PROPERTY(int size READ size)

public:
    Database(const Database&) = delete; // disable copy for singleton
    static Database *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    ~Database() override;

    // from file
    QStringList getBookDirs();
    QStringList getBookFiles(const QString &xPath);

    // database
    void initDatabase();
    void setInfo(const QString &xKey, const QString &xValue);
    QVariant getInfo(const QString &xKey);
    void writeChapter(const Chapter &xChapter);
    Chapter getChapter(const QString &xPath);
    void writeBook(const Book &xBook);
    Book getBook(const QString &xPath);


    // library
    QString libraryPath() const;
    void setLibraryPath(QString &xPath);
    int size() const;
    bool isEmpty() const;
    QVector<Book> getLibraryItems();
    Book * getLibraryItem(QString &xPath);
    Book * getNextLibraryItem(QString &xPath);

signals:
    void pathChanged();
    void libraryUpdated();
    void currentItemChanged();

public slots:
    void updateLibrary();

private:
    explicit Database(QObject *parent = nullptr);
    QVector<Book> mLibraryItems;
    QString mLibraryPath;
    QSqlDatabase mDatabase;
    QStringList mFileFilters = { "*.mp3", "*.ogg", "*.wav" };

};

#endif // DATABASE_H
