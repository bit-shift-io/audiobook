#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QVector>
#include "book.h"

class Library : public QObject
{
    Q_OBJECT
public:
    explicit Library(QObject *parent = nullptr);

protected:
    QString library_directory;
    QVector<Book> book_list;

signals:
    void library_updated();

public slots:
    void set_library_directory(QString &dir);
    void update_library_list();
    QVector<Book> get_book_list();
};

#endif // PLAYLIST_H
