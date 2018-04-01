#include "library.h"
#include "book.h"
#include "audiohelper.h"
#include <QDirIterator>
#include <QDir>
#include <QDebug>
#include <QtAlgorithms>

Library::Library(QObject *parent) : QObject(parent)
{

}

void Library::set_library_directory(QString &dir) {
    library_directory = dir;
    update_library_list();
    emit library_updated();
}

QVector<Book> Library::get_book_list() {
    return book_list;
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

            // get abs paths and file times
            QStringList abs_current_files;

            for (auto current_file : current_files) {
                QString abs_current_file = current_dir.absoluteFilePath(current_file);
                uint current_length = AudioHelper::get_time_msec(abs_current_file);

                abs_current_files << abs_current_file;
                book.chapter_times.append(current_length);
                book.time += current_length;
            }

            book.title = lib_dir.relativeFilePath(directories.filePath());
            book.files = abs_current_files;
            book.chapters = current_files;
            book.directory = lib_dir.relativeFilePath(directories.filePath());
            book_list.append(book);
        }

    }

    // sort by title
    qSort(book_list.begin(), book_list.end(), caseInsensitiveLessThan);


}
