#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <QAbstractTableModel>

class Library;

class LibraryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    LibraryModel(QObject *parent, Library *p_library);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QString get_display_time(uint p_time);

protected:
    Library *library;

public slots:
    void update_data();
};

#endif // LIBRARYMODEL_H
