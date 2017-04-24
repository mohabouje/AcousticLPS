#include "beaconlistmodel.h"

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
    const QBeacon beacon = _beacons.at(row);
    switch (role) {
    case Qt::DisplayRole:
        return QVariant::fromValue<QString>(beacon.universalUniqueIdentifier().toString());
    case Qt::UserRole:
        return QVariant::fromValue<QBeacon>(beacon);
    default:
        return QVariant();
    }
}


