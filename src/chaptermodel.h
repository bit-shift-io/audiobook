#ifndef CHAPTERMODEL_H
#define CHAPTERMODEL_H

#include <QAbstractListModel>

class Book;
class Library;

class ChapterModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ChapterModel(QObject *parent = nullptr);

    // list of accesable properties/roles/map/bindings
    enum {
        ChapterIndexRole,
        TitleRole,
        FileNameRole,
        DurationRole,
        CurrentItemRole,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void refresh();

    // hashmap to store properties/roles
    // map/bind qml to cpp
    virtual QHash<int, QByteArray> roleNames() const override {
        QHash<int, QByteArray> names;
        names[ChapterIndexRole] = "chapterIndex";
        names[TitleRole] = "title";
        names[FileNameRole] = "fileName";
        names[DurationRole] = "duration";
        names[CurrentItemRole] = "isCurrentItem";
        return names;
    }


};

#endif // CHAPTERMODEL_H
