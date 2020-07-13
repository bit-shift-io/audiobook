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
    Q_PROPERTY(int size READ size)
    Q_PROPERTY(int activeItem READ activeItem WRITE setActiveItem NOTIFY activeItemChanged)

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
    //const Book* findByPath(const QString &dir);
    //int getBookIndex(const Book &book);

    // active library item
    void setActiveItem(int xIndex);
    int activeItem();
    const Book* getActiveItem();

signals:
    void pathChanged();
    void libraryUpdated();
    void activeItemChanged();

public slots:
    void update();

private:
    int mActiveItem = -1;
    QVector<Book> mLibraryItems;
    QString mPath;
    explicit Library(QObject *parent = nullptr);

};

#endif // LIBRARY_H
