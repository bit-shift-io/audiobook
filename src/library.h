#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QVector>
#include <QFileInfo>
#include "book.h"
#include "database.h"

class QQmlEngine;
class QJSEngine;

class Library : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(int size READ size)
    Q_PROPERTY(QString activeItem WRITE setActiveItem NOTIFY activeItemChanged)

public:
    Library(const Library&) = delete; // disable copy for singleton
    static Library *instance();
    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

    // library path
    QString path() const;
    void setPath(QString &xPath);

    // library size
    int size() const;
    bool isEmpty() const;

    QVector<Book> getLibraryItems();
    const Book* getLibraryItem(const QString &xTitle);

    // active library item
    void setActiveItem(QString xTitle);
    const Book* activeItem();
    const Book* getActiveItem();

signals:
    void pathChanged();
    void libraryUpdated();
    void activeItemChanged();

public slots:
    void update();

protected:

private:
    QVector<Book> mLibraryItems;
    const Book *mActiveItem = nullptr;
    QString mPath;
    Database *mDatabase = nullptr;
    explicit Library(QObject *parent = nullptr);

};

#endif // LIBRARY_H
