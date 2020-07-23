#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QVector>
#include "chapter.h"

class Book
{

public:
    Book() {};
    QString title;
    QString artist;
    QString path;
    QVector<Chapter> chapters;
    qint64 duration = 0;

    //void addChapter(const Chapter &xChapter);
    //bool isEmpty();

    bool operator==(const Book& rhs) {
        if (path == rhs.path)
                return true;
        return false;
    };
};

#endif // BOOK_H
