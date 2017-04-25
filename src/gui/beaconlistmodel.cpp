#include "beaconlistmodel.h"
#include "helper.h"
#include <model/qenvironement.h>

BeaconListModel::BeaconListModel(QObject *parent) : QAbstractListModel(parent) {

}

int BeaconListModel::rowCount(const QModelIndex &) const {
    return QEnvironement::instance()->beaconsCount();
}

QVariant BeaconListModel::data(const QModelIndex &index, int role) const {
    const int column = index.column();
    const QBeacon beacon = QEnvironement::instance()->beacon(index.row());
    if (column == StateColumn && role == Qt::DecorationRole) {
        return QVariant::fromValue<QIcon>(SIGNAL_OFF_ICON);
    } else if (column == NameColumn && role == Qt::DisplayRole) {
        return QVariant::fromValue<QString>(beacon->name());
    } else if (column == SNRColumn && role == Qt::DisplayRole) {
        return QVariant::fromValue<QString>(QString::number(beacon->SNR()));
    } else if (role == Qt::UserRole) {
        return QVariant::fromValue<QBeacon>(beacon);
    } else {
        return QVariant();
    }
}


