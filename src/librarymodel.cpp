#include <QDebug>
#include "librarymodel.h"
#include "library.h"
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
    return Library::instance()->size();
}


QVariant LibraryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || Library::instance()->isEmpty())
            return QVariant();

    const Book &book = Library::instance()->getLibraryItems().at(index.row());

    switch (role) {
        case LibraryIndexRole:
            return QVariant(index.row());
        case TitleRole:
            return QVariant(book.title);
        case ChaptersRole:
            return QVariant(book.chapter_titles.count());
        case DurationRole:
            return QVariant(Util::getDisplayTime(book.time));
    }
    return QVariant();
}
