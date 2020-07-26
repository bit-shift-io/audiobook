#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QVector>
#include <QFileInfo>
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


    qint64 getStartProgressChapter(int xChapterIndex) {
        qint64 start_pos = 0;
        for(int i = 0; i<xChapterIndex; ++i) {
            start_pos += chapters[i].duration;
        }
        return start_pos;
    }


    int getChapterIndex(qint64 xPosition) {
        // loop over chapters, reduce position by each chapter length till we are in the correct chapter
        for(int i = 0; i < chapters.length(); ++i) {
            if (xPosition < chapters[i].duration) {
                return i;
            }
            xPosition -= chapters[i].duration;
        }
        return 0;
    }


    qint64 getChapterPosition(qint64 xProgress) {
        int chapter_index = 0;
        qint64 chapter_position = xProgress;
        // loop over chapters, reduce position by each chapter length till we are in the correct chapter
        for(int i = 0; i < chapters.length(); ++i) {
            if (chapter_position < chapters[i].duration) {
                chapter_index = i;
                break;
            }
            chapter_position -= chapters[i].duration;
        }
        return chapter_position;
    }


    void ready() {
        if (!isEmpty()) {
            if (chapters.size() == 1) {
                title = chapters[0].title;
            } else {
                if (chapters[0].title == chapters[1].title)
                    title = chapters[0].title;
            }

            artist = chapters[0].artist;
            genre = chapters[0].genre;
            year = chapters[0].year;
        }

        if (title.isEmpty())
            title = QFileInfo(path).baseName().replace("_", " ");
    }
};

#endif // BOOK_H
