#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QStringList>

class Book
{

public:
    Book();
    QString title;
    QStringList chapters;
    QStringList chapter_times;

    QString directory;
    QStringList files;

    QString time;

};

#endif // BOOK_H
