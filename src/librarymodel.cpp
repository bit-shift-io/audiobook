#include <QDebug>
#include "librarymodel.h"
#include "database.h"
#include "util.h"


LibraryModel::LibraryModel(QObject *parent)
    : QAbstractListModel(parent)
{
}


void LibraryModel::refresh() {
    beginResetModel();
    endResetModel();
}


int LibraryModel::rowCount(const QModelIndex & /*parent*/) const
{
    return Database::instance()->size();
}


QVariant LibraryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || Database::instance()->isEmpty())
            return QVariant();

    const Book &book = Database::instance()->getLibraryItems().at(index.row());

    switch (role) {
        case LibraryIndexRole:
            return QVariant(index.row());
        case TitleRole:
            return QVariant(book.title);
        case ChaptersRole:
            return QVariant(book.chapters.count());
        case DurationRole:
            return QVariant(Util::getDisplayTime(book.duration));
        case ArtistRole:
            return QVariant(book.artist);
    case PathRole:
        return QVariant(book.path);
    }
    return QVariant();
}
