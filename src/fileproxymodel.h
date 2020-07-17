#ifndef FILEPROXYMODEL_H
#define FILEPROXYMODEL_H

#include <QAbstractListModel>
#include <QFileSystemModel>
#include <QUrl>


class FileProxyModel  : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QUrl folder READ folder WRITE setFolder NOTIFY folderChanged)
    Q_PROPERTY(QUrl parentFolder READ parentFolder NOTIFY folderChanged)

public:
    // add new roles to QFileSystemModel
    enum Roles {
        FileIconRole = Qt::DecorationRole,
        FilePathRole = Qt::UserRole + 1,
        FileNameRole = Qt::UserRole + 2,
        FilePermissions = Qt::UserRole + 3
    };

    /*
    // add new roles to QFileSystemModel
    enum Roles  {
        SizeRole = Qt::UserRole + 4,
        DisplayableFilePermissionsRole = Qt::UserRole + 5,
        LastModifiedRole = Qt::UserRole + 6,
        UrlStringRole = Qt::UserRole + 7
    };*/

    Q_ENUM(Roles) // expose to qml

    FileProxyModel(QObject *parent = 0);
    ~FileProxyModel();

    QUrl folder() const;
    void setFolder(const QUrl &folder);

    QUrl parentFolder() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void UpdateData();

    QHash<int,QByteArray> roleNames() const Q_DECL_OVERRIDE
    {
         QHash<int, QByteArray> result = mFileSystemModel->roleNames();
         return result;
    }

Q_SIGNALS:
    void folderChanged();

private Q_SLOTS:
    void refresh();
    void inserted(const QModelIndex &index, int start, int end);
    void removed(const QModelIndex &index, int start, int end);
    void handleDataChanged(const QModelIndex &start, const QModelIndex &end);

private:
    QFileSystemModel *mFileSystemModel = nullptr;
    QUrl mFolder;
    QModelIndex mFolderIndex;
    int mCount;

};

#endif // FILEPROXYMODEL_H
