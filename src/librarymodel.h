#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <QAbstractListModel>

class Book;
class Library;

class LibraryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit LibraryModel(QObject *parent = nullptr);

    // list of accesable properties/roles/map/bindings
    enum {
        TitleRole,
        ChaptersRole,
        DurationRole,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // hashmap to store properties/roles
    virtual QHash<int, QByteArray> roleNames() const override;

    void UpdateData();
};

#endif // LIBRARYMODEL_H
