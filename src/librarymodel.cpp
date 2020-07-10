#include "librarymodel.h"
#include "library.h"
#include "util.h"


LibraryModel::LibraryModel(QObject *parent, Library *p_library) :QAbstractTableModel(parent)
{
    library = p_library;
    // connect this model to the library update function
    connect(p_library, &Library::pathChanged, this, &LibraryModel::update_data);
}

void LibraryModel::update_data() {
    beginResetModel();
    endResetModel();
}

int LibraryModel::rowCount(const QModelIndex & /*parent*/) const
{
   return library->getBooks().count();
}

int LibraryModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant LibraryModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole)
    {
        switch (index.column())
        {
        case 0:
            return Qt::AlignLeft;
        case 1:
            return Qt::AlignCenter;
        case 2:
            return Qt::AlignCenter;
        }
    }

    if (role == Qt::DisplayRole)
    {
        const Book &book = library->getBooks().at(index.row());
        switch (index.column())
        {
        case 0:
            return book.title;
        case 1:
            return book.chapter_titles.count();
        case 2:
            return Util::get_display_time(book.time);
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
