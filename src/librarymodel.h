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
        LibraryIndexRole,
        TitleRole,
        ChaptersRole,
        DurationRole,
        ArtistRole,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void refresh();

    // hashmap to store properties/roles
    // map/bind qml to cpp
    virtual QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> names;
        names[LibraryIndexRole] = "libraryIndex";
        names[TitleRole] = "title";
        names[ChaptersRole] = "chapters";
        names[DurationRole] = "duration";
        names[ArtistRole] = "artist";
        return names;
    }


};

#endif // LIBRARYMODEL_H
