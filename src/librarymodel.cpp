#include "librarymodel.h"
#include "library.h"
#include "util.h"


LibraryModel::LibraryModel(QObject *parent)
    : QAbstractListModel(parent)
{
}


void LibraryModel::UpdateData() {
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
        case TitleRole:
            return QVariant(book.title);
        case ChaptersRole: {
            return QVariant(book.chapter_titles.count());
        }
        case DurationRole:
            return QVariant(Util::getDisplayTime(book.time));
    }
    return QVariant();
}



QHash<int, QByteArray> LibraryModel::roleNames() const
{
    // map/bind qml to cpp
    QHash<int, QByteArray> names;
    names[TitleRole] = "title";
    names[ChaptersRole] = "chapters";
    names[DurationRole] = "duration";
    return names;
}
