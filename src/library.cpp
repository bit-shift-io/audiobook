#include <QDirIterator>
#include <QDir>
#include <QDebug>
#include <QtAlgorithms>
#include <QStandardPaths>

#include "library.h"
#include "book.h"
#include "util.h"
#include "settings.h"
#include "database.h"

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


void Library::setCurrentItem(QString &xIndex)
{
    if (mCurrentItem == xIndex || xIndex.isEmpty())
        return;

    mCurrentItem = xIndex;
    emit currentItemChanged();
}


QString Library::currentItem()
{
    return mCurrentItem;
}

const Book* Library::getCurrentItem()
{
    for (Book &item: mLibraryItems){
        if (item.path == mCurrentItem)
            return &item;
    }

    return nullptr;
}


QVector<Book> Library::getLibraryItems() {
    return mLibraryItems;
}


bool caseInsensitiveLessThan(const Book &s1, const Book &s2) {
    return s1.title.toLower() < s2.title.toLower();
}


void Library::update() {
    // TODO: delete old books

    // set library path
    Database::instance()->instance()->setInfo("library_path", mPath);

    // loop dirs
    QDir lib_dir(mPath);
    QDirIterator directories(mPath, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList file_filters;
    file_filters << "*.mp3" << "*.wav" << "*.ogg";

    while(directories.hasNext()) {
        directories.next();

        // does folder contain any audio files? if we have audio files, this is a book
        QDir current_dir(directories.filePath());
        QStringList dir_list = current_dir.entryList(file_filters, QDir::NoDotAndDotDot | QDir::Files);
        if (dir_list.count() == 0)
            continue;


        // new book for each directory
        QString book_path = "/" + lib_dir.relativeFilePath(directories.filePath());
        Book book = Database::instance()->getBook(book_path);

        if (book.isEmpty()) {
            qDebug() << "new book";

            // get book from file
            QFileInfo first_file = current_dir.absoluteFilePath(dir_list[0]);
            book.artist = Util::getTagArtist(first_file.absoluteFilePath());
            book.title = Util::getTagAlbum(first_file.absoluteFilePath());
            if (book.title.isEmpty())
                book.title = lib_dir.relativeFilePath(directories.filePath()).replace("_", " ");

            // get abs paths and file times
            QStringList abs_current_files;

            for (auto current_file : dir_list) {
                // access from db
                Chapter c = Database::instance()->instance()->getChapter(book.path + "/" + current_file);

                if (c.duration == -1) {
                    qDebug() << "new file found";
                    // scan file and update db
                    QFileInfo abs_current_file = current_dir.absoluteFilePath(current_file);
                    uint current_length = Util::getTimeMSec(abs_current_file.absoluteFilePath());

                    c.path = abs_current_file.absoluteFilePath().replace(mPath, "");
                    c.duration = current_length;

                    c.title = Util::getTagTitle(abs_current_file.absoluteFilePath());
                    if (c.title.isEmpty())
                        c.title = Util::toCamelCase(abs_current_file.baseName().replace("_", " "));

                    c.year = Util::getTagYear(abs_current_file.absoluteFilePath());
                    if (c.year == -1)
                        c.year = abs_current_file.birthTime().date().year();

                    Database::instance()->instance()->setChapter(c);
                }

                // assign chapter to book
                book.addChapter(c);
            }

            // write new database entry
            Database::instance()->setBook(book);
        }

        // assign book to library
        mLibraryItems.append(book);

    } // end dir loop

    // sort by title
    qSort(mLibraryItems.begin(), mLibraryItems.end(), caseInsensitiveLessThan);

    emit libraryUpdated();
}

