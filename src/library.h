#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QVector>
#include "book.h"
#include <QFileInfo>

class QQmlEngine;
class QJSEngine;

class Library : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)

public:
    Library(const Library&) = delete; // disable copy for singleton
    static Library *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    QString path() const;
    void setPath(QString &xPath);

signals:
    void pathChanged();
    void libraryUpdated();

public slots:
    void update();
    QVector<Book> getBooks();
    const Book* findByPath(const QString& dir);
    int getBookIndex(const Book& book);

private:
    QVector<Book> book_list;
    QString mPath;
    explicit Library(QObject *parent = nullptr);

};

#endif // LIBRARY_H
