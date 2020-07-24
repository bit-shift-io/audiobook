#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QVector>
#include "chapter.h"

class Book
{

public:
    Book() {}
    QString title;
    QString artist;
    QString year;
    QString genre;
    QString path;
    QVector<Chapter> chapters;
    qint64 duration = 0;
    qint64 progress = 0;

    bool isEmpty() { return chapters.isEmpty(); }

    bool operator==(const Book& rhs) {
        if (path == rhs.path)
                return true;
        return false;
    };

    void addChapter(const Chapter &xChapter) {
        duration += xChapter.duration;
        chapters.append(xChapter);
    }
};

#endif // BOOK_H
