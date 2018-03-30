#include "library.h"
#include "book.h"
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

bool caseInsensitiveLessThan(const Book &s1, const Book &s2)
{
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

        // get abs paths
        QStringList abs_current_files;
        for (QStringList::Iterator it=current_files.begin(); it != current_files.end(); ++it) {
            abs_current_files << current_dir.absoluteFilePath(*it);
        }

        if (current_files.count() > 0) {
            Book book;
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
