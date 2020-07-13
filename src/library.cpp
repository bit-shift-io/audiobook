#include <QDirIterator>
#include <QDir>
#include <QDebug>
#include <QtAlgorithms>
#include <QStandardPaths>

#include "library.h"
#include "book.h"
#include "util.h"
#include "settings.h"

Library::Library(QObject *parent) :
    QObject(parent)
{
    // mPath from settings
    mPath = Settings::value("library_path", QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath())).toString();
    update();
}

Library *Library::instance()
{
    static Library* instance = new Library;
    return instance;
}

QObject *Library::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return Library::instance(); // C++ and QML instance
}

QString Library::path() const
{
    return mPath;
}

void Library::setPath(QString &xPath) {
    xPath = xPath.replace("file://","");
    if (xPath == mPath)
        return;
    mPath = xPath;
    Settings::setValue("library_path", mPath);
    qDebug() << mPath;
    update();
    emit pathChanged();
}

int Library::size() const
{
    return mLibraryItems.size();
}

bool Library::isEmpty() const
{
    return mLibraryItems.isEmpty();
}

/*
const Book* Library::findByPath(const QString& dir) {
    Book b;
    b.directory=dir;
    int i = mLibraryItems.indexOf(b);
    if (i == -1)
        return NULL;

    return &mLibraryItems[i];
}
*/

/*
int Library::getBookIndex(const Book& book) {
    int i = mLibraryItems.indexOf(book);
    return i;
}*/

void Library::setActiveItem(int xIndex)
{
    if (mActiveItem == xIndex)
        return;
    mActiveItem = xIndex;
    emit activeItemChanged();
}

int Library::activeItem()
{
    return mActiveItem;
}

const Book* Library::getActiveItem()
{
    if (mActiveItem == -1 || mLibraryItems.isEmpty() || mActiveItem >= mLibraryItems.size())
        return nullptr;

    return &mLibraryItems[mActiveItem];
}


QVector<Book> Library::getLibraryItems() {
    return mLibraryItems;
}


bool caseInsensitiveLessThan(const Book &s1, const Book &s2) {
    return s1.title.toLower() < s2.title.toLower();
}

void Library::update() {
    //QStringList all_dirs;
    QDir lib_dir(mPath);
    QDirIterator directories(mPath, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

    QStringList file_filters;
    file_filters << "*.mp3" << "*.wav" << "*.ogg";


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
                uint current_length = Util::getTimeMSec(abs_current_file.absoluteFilePath());

                book.chapter_files.append(abs_current_file.absoluteFilePath());
                book.chapter_times.append(current_length);
                book.chapter_titles.append(abs_current_file.baseName());
                book.time += current_length;
            }

            mLibraryItems.append(book);
        }

    }

    // sort by title
    qSort(mLibraryItems.begin(), mLibraryItems.end(), caseInsensitiveLessThan);

    emit libraryUpdated();
}

