#include "libraryfilterproxy.h"
#include "librarymodel.h"
#include <QDebug>


LibraryFilterProxy::LibraryFilterProxy(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

bool LibraryFilterProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    // Here we can specify whatever filter logic we need to and can check multiple Roles. Below
    // we are simply checking the Value role to see if that value stored there is even, if so include the
    // data entry in this proxy model.
    if ( this->sourceModel() == nullptr )
        return false;

    QRegExp reg = filterRegExp();

    QModelIndex index0 = sourceModel()->index(sourceRow, 0, sourceParent);
    if (!index0.isValid())
        return false;

    QVariant value_role = index0.data( LibraryModel::TitleRole );
    if (value_role.toString().toLower().contains(reg.pattern().toLower()))
        return true;

    return false;
}
