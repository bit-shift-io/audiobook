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
    return book->chapters.size();
}


QVariant ChapterModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || Library::instance()->isEmpty())
            return QVariant();

    const Book *book = Library::instance()->getActiveItem();
    if (book == nullptr)
        return QVariant();

    const Chapter c = book->chapters.at(index.row());

    switch (role) {
        case ChapterIndexRole:
            return QVariant(index.row());
        case TitleRole:
            return QVariant(c.title);
        case FileNameRole:
            return QVariant(c.filePath);
        case DurationRole:
            return QVariant(Util::getDisplayTime(c.duration));
    }
    return QVariant();
}
