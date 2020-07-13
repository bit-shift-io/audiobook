#ifndef LIBRARYMODELPROXY_H
#define LIBRARYMODELPROXY_H

#include <QObject>
#include <QSortFilterProxyModel>

class LibraryFilterProxy : public QSortFilterProxyModel
{
public:
    LibraryFilterProxy(QObject *parent = 0);
    bool filterAcceptsRow( int source_row, const QModelIndex& source_parent ) const override;
};

#endif // LIBRARYMODELPROXY_H
