#include "beaconlistmodel.h"
#include "helper.h"

BeaconListModel::BeaconListModel(QObject *parent) : QAbstractListModel(parent) {

}

bool BeaconListModel::remove(const QBeacon &beacon) {
    return _beacons.removeAll(beacon) > 0;
}

void BeaconListModel::insert(const QBeacon &beacon) {
    if (!_beacons.contains(beacon)) {
        _beacons.append(beacon);
    }
}

void BeaconListModel::insert(const QList<QBeacon> &beacons) {
    _beacons += beacons;
}

QVariant BeaconListModel::data(const QModelIndex &index, int role) const {
    const int row = index.row();
    const int column = index.column();
    const QBeacon beacon = _beacons.at(row);
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


