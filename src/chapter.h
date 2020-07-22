#ifndef CHAPTER_H
#define CHAPTER_H

#include <QObject>

class Chapter
{
public:
    Chapter();
    QString filePath;
    QString artist;
    int year = -1;
    QString genre;
    QString title;
    qint64 duration;
    int size;

    bool operator==(const Chapter& rhs);
};

#endif // CHAPTER_H
