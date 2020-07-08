#include <QDirIterator>
#include <QDir>
#include <QDebug>
#include <QtAlgorithms>
#include "library.h"
#include "book.h"
#include "audioutil.h"

Library::Library(QObject *parent) : QObject(parent)
{

}

void Library::set_library_directory(QString &dir) {
    library_directory = dir;
    update_library_list();
    emit library_changed();
}


const Book* Library::find_by_directory(const QString& dir) {
    Book b;
    b.directory=dir;
    int i = book_list.indexOf(b);
    if (i == -1)
        return NULL;

    return &book_list[i];
}

int Library::get_book_index(const Book& book) {
    int i = book_list.indexOf(book);
    return i;
}

QVector<Book> Library::get_book_list() {
    return book_list;
}

QString Library::get_library_directory() {
    return library_directory;
}

bool caseInsensitiveLessThan(const Book &s1, const Book &s2) {
    return s1.title.toLower() < s2.title.toLower();
}

void Library::update_library_list() {
    //QStringList all_dirs;
    QDir lib_dir(library_directory);
    QDirIterator directories(library_directory, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

    QStringList file_filters;
    file_filters << "*.mp3" << "*.wav";

    while(directories.hasNext()){
        directories.next();

        // does folder contain any audio files? if we have audio files, this is a book
        QDir current_dir(directories.filePath());
        QStringList current_files = current_dir.entryList(file_filters, QDir::NoDotAndDotDot | QDir::Files);

        if (current_files.count() > 0) {
            Book book;

            book.title = lib_dir.relativeFilePath(directories.filePath());
            book.directory = lib_dir.relativeFilePath(directories.filePath());

            // get abs paths and file times
            QStringList abs_current_files;

            for (auto current_file : current_files) {
                QFileInfo abs_current_file = current_dir.absoluteFilePath(current_file);
                uint current_length = AudioUtil::get_time_msec(abs_current_file.absoluteFilePath());

                book.chapter_files.append(abs_current_file.absoluteFilePath());
                book.chapter_times.append(current_length);
                book.chapter_titles.append(abs_current_file.baseName());
                book.time += current_length;
            }

            book_list.append(book);
        }

    }

    // sort by title
    qSort(book_list.begin(), book_list.end(), caseInsensitiveLessThan);


}

