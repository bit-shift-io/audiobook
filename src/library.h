#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QVector>
#include "book.h"
#include <QFileInfo>

class Library : public QObject
{
    Q_OBJECT
public:
    explicit Library(QObject *parent = nullptr);

protected:
    QString library_directory;
    QVector<Book> book_list;

signals:
    void library_changed();

public slots:
    void set_library_directory(QString &dir);
    void update_library_list();
    QVector<Book> get_book_list();
    QString get_library_directory();
    const Book* find_by_directory(const QString& dir);
    int get_book_index(const Book& book);

};

#endif // PLAYLIST_H
