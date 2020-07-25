#ifndef CHAPTER_H
#define CHAPTER_H

#include <QObject>

class Chapter
{
public:
    Chapter() {};
    QString path;
    QString artist;
    int year = -1;
    QString genre;
    QString title;
    qint64 duration = -1;

    bool isEmpty() { return duration == -1; };

    bool operator==(const Chapter& rhs) {
        if (path == rhs.path)
                return true;
        return false;
    };
};

#endif // CHAPTER_H
