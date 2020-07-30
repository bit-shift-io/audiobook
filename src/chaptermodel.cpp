#include <QDebug>
#include "chaptermodel.h"
#include "player.h"
#include "util.h"


ChapterModel::ChapterModel(QObject *parent)
    : QAbstractListModel(parent)
{
    // connect library
    connect(Player::instance(), &Player::currentIndexChanged, this, &ChapterModel::refresh);
}


void ChapterModel::refresh() {
    beginResetModel();
    endResetModel();
}


int ChapterModel::rowCount(const QModelIndex & /*parent*/) const
{
    Book * book = Player::instance()->getCurrentItem();
    if (book == nullptr)
        return 0;
    return book->chapters.size();
}


QVariant ChapterModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();

    const Book *book = Player::instance()->getCurrentItem();
    if (book == nullptr)
        return QVariant();

    const Chapter c = book->chapters.at(index.row());

    switch (role) {
        case ChapterIndexRole:
            return QVariant(index.row());
        case TitleRole:
            return QVariant(c.title);
        case FileNameRole:
            return QVariant(c.path);
        case DurationRole:
            return QVariant(Util::getDisplayTime(c.duration));
        case CurrentItemRole:
            return QVariant(index.row() == Player::instance()->chapterIndex());
    }
    return QVariant();
}
