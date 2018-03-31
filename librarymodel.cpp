#include "librarymodel.h"
#include "library.h"

LibraryModel::LibraryModel(QObject *parent, Library *p_library) :QAbstractTableModel(parent)
{
    library = p_library;
    // connect this model to the library update function
    connect(p_library, SIGNAL(library_updated()), this, SLOT(update_data()));
}

void LibraryModel::update_data() {
    beginResetModel();
    endResetModel();
}

int LibraryModel::rowCount(const QModelIndex & /*parent*/) const
{
   return library->get_book_list().count();
}

int LibraryModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant LibraryModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        const Book &book = library->get_book_list().at(index.row());
        switch (index.column())
        {
        case 0:
            return book.title;
        case 1:
            return book.chapters.count();
        case 2:
            return book.chapter_times.count();
        }
    }
    return QVariant();
}


QVariant LibraryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Title");
            case 1:
                return QString("Chapters");
            case 2:
                return QString("Time");
            }
        }
    }
    return QVariant();
}