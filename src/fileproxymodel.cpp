#include <QDebug>
#include <QAbstractItemModel>
#include "fileproxymodel.h"
#include "util.h"

FileProxyModel::FileProxyModel(QObject *parent)
    : QAbstractListModel(parent)
{
    mFileSystemModel = new QFileSystemModel(this);
    mFileSystemModel->setFilter(QDir::AllDirs | QDir::AllEntries); //QDir::AllDirs | QDir::NoDot); // | QDir::NoDotAndDotDot |
    mFileSystemModel->setResolveSymlinks(true);
    QString path = Util::getHomeLocation();
    path = Util::appendFile(path);
    path = QString("file:///home");
    path = QString("/");
    qDebug() << path;
    mFileSystemModel->setRootPath(path); // TODO: this returns a model!

    connect(mFileSystemModel, &QAbstractItemModel::rowsInserted, this, &FileProxyModel::inserted);
    connect(mFileSystemModel, &QAbstractItemModel::rowsRemoved, this, &FileProxyModel::removed);
    connect(mFileSystemModel, &QAbstractItemModel::dataChanged, this, &FileProxyModel::handleDataChanged);
    //connect(mFileSystemModel, &QAbstractItemModel::modelReset, this, &FileProxyModel::refresh);
    //connect(mFileSystemModel, &QAbstractItemModel::layoutChanged, this, &FileProxyModel::refresh);
    connect(mFileSystemModel, &QFileSystemModel::directoryLoaded, this, &FileProxyModel::refresh);

    setFolder(QUrl(path));
}


FileProxyModel::~FileProxyModel()
{
    delete mFileSystemModel;
}


QUrl FileProxyModel::folder() const
{
    return mFolder;
}


void FileProxyModel::setFolder(const QUrl &folder)
{
    if (mFolder == folder)
        return;

    QModelIndex index = mFileSystemModel->index(folder.toLocalFile());

    if ((index.isValid() && mFileSystemModel->isDir(index)) || folder.toLocalFile().isEmpty()) {
        mFolder = folder;
        QMetaObject::invokeMethod(this, "refresh", Qt::QueuedConnection);
        emit folderChanged();
    }
}


QUrl FileProxyModel::parentFolder() const
{
    QString localFile = mFolder.toLocalFile();
    if (!localFile.isEmpty()) {
        QDir dir(localFile);
#if defined(Q_OS_SYMBIAN) || defined(Q_OS_WIN)
        if (dir.isRoot())
            dir.setPath("");
        else
#endif
            dir.cdUp();
        localFile = dir.path();
    } else {
        int pos = mFolder.path().lastIndexOf(QLatin1Char('/'));
        if (pos == -1)
            return QUrl();
        localFile = mFolder.path().left(pos);
    }
    return QUrl::fromLocalFile(localFile);
}


int FileProxyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mCount;
}


QVariant FileProxyModel::data(const QModelIndex &index, int role) const
{
    //Roles val = static_cast<Roles>(role);
    QVariant rv;
    QModelIndex modelIndex = mFileSystemModel->index(index.row(), 0, mFolderIndex);
    if (modelIndex.isValid()) {
        if (role == FileNameRole)
            rv = mFileSystemModel->data(modelIndex, Roles::FileNameRole).toString();
        else if (role == FilePathRole)
            rv = QUrl::fromLocalFile(mFileSystemModel->data(modelIndex, Roles::FilePathRole).toString());
    }
    return rv;
}


void FileProxyModel::refresh()
{
    qDebug() << "refresh";

    mFolderIndex = QModelIndex();
    if (mCount) {
        emit beginRemoveRows(QModelIndex(), 0,mCount-1);
        mCount = 0;
        emit endRemoveRows();
    }

    mFolderIndex = mFileSystemModel->index(mFolder.toLocalFile());
    int newcount = mFileSystemModel->rowCount(mFolderIndex);
    if (newcount) {
        emit beginInsertRows(QModelIndex(), 0, newcount-1);
        mCount = newcount;
        emit endInsertRows();
    }
}

void FileProxyModel::inserted(const QModelIndex &index, int start, int end)
{
    if (index == mFolderIndex) {
        emit beginInsertRows(QModelIndex(), start, end);
        mCount = mFileSystemModel->rowCount(mFolderIndex);
        qDebug() << "inserted" << mCount << mFolderIndex;
        emit endInsertRows();
    }
}

void FileProxyModel::removed(const QModelIndex &index, int start, int end)
{
    qDebug() << "removed";
    if (index == mFolderIndex) {
        emit beginRemoveRows(QModelIndex(), start, end);
        mCount = mFileSystemModel->rowCount(mFolderIndex);
        emit endRemoveRows();
    }
}

void FileProxyModel::handleDataChanged(const QModelIndex &start, const QModelIndex &end)
{
    qDebug() << "handledatachanged";
    if (start.parent() == mFolderIndex)
        emit dataChanged(index(start.row(),0), index(end.row(),0));
}
