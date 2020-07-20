#include <QDebug>
#include "chaptermodel.h"
#include "player.h"
#include "library.h"
#include "util.h"


ChapterModel::ChapterModel(QObject *parent)
    : QAbstractListModel(parent)
{
    // connect library
    connect(Player::instance(), &Player::currentIndexChanged, this, &ChapterModel::chapterIndexChanged);
}


void ChapterModel::refresh() {
    beginResetModel();
    endResetModel();
}

void ChapterModel::chapterIndexChanged(int xIndex)
{
    refresh();
}


int ChapterModel::rowCount(const QModelIndex & /*parent*/) const
{
    const Book *book = Library::instance()->getActiveItem();
    if (book == nullptr)
        return 0;
    return Library::instance()->getActiveItem()->chapter_files.size();
}


QVariant ChapterModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || Library::instance()->isEmpty())
            return QVariant();

    const Book *book = Library::instance()->getActiveItem();
    if (book == nullptr)
        return QVariant();

    switch (role) {
        case ChapterIndexRole:
            return QVariant(index.row());
        case TitleRole:
            return QVariant(book->chapter_titles.at(index.row()));
        case FileNameRole:
            return QVariant(book->chapter_files.at(index.row()));
        case DurationRole:
            return QVariant(Util::getDisplayTime(book->chapter_times.at(index.row())));
    }
    return QVariant();
}
