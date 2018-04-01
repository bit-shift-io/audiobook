#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QStringList>
#include <QTime>
#include <QVector>

class Book
{

public:
    Book();
    QString title;
    QStringList chapters;
    QVector<uint> chapter_times;

    QString directory;
    QStringList files;

    uint time;

};

#endif // BOOK_H
