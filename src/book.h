#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QVector>
#include "chapter.h"

class Book
{

public:
    Book();
    QString title;
    QString artist;
    QString directory;
    QVector<Chapter> chapters;
    qint64 duration;

    bool operator==(const Book& rhs);
};

#endif // BOOK_H
