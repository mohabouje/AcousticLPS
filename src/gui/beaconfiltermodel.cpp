#include "beaconfiltermodel.h"
#include "helper.h"
#include <QModelIndex>
BeaconFilterModel::BeaconFilterModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}


bool BeaconFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    const QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    const QVariant data =  index.data(Qt::UserRole);
    if (data.canConvert<QBeacon>()) {
        const QBeacon beacon = data.value<QBeacon>();
        return beacon->name().contains(_nameFilter);
    }
    return false;
}

bool BeaconFilterModel::lessThan(const QModelIndex &source_right, const QModelIndex &source_left) const {
    const QBeacon rightBeacon = Gui::qBeaconFromQModelIndex(source_right);
    const QBeacon leftBeacon = Gui::qBeaconFromQModelIndex(source_left);
    switch (_currentSort) {
    case SortByUuid:
        return rightBeacon->universalUniqueIdentifier() < leftBeacon->universalUniqueIdentifier();
    case SortByName:
        return rightBeacon->name() < leftBeacon->name();
    case SortByIdentifier:
        return rightBeacon->identifier() < leftBeacon->identifier();
    case SortBySNR:
        return rightBeacon->SNR() < leftBeacon->SNR();
    default:
       return true;
    }
}








