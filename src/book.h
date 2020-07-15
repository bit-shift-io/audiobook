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
    QString directory;
    QStringList chapter_titles;
    QStringList chapter_files;
    QVector<uint> chapter_times;
    qint64 time;

    bool operator==(const Book& rhs);
};

#endif // BOOK_H
