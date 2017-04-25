#include "beaconlistmodel.h"
#include "helper.h"
#include <model/qenvironement.h>
#include <QDebug>
BeaconListModel::BeaconListModel(QObject *parent) : QAbstractTableModel(parent) {

}

int BeaconListModel::rowCount(const QModelIndex &) const {
    return QEnvironement::instance()->beaconsCount();
}

QVariant BeaconListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation !=  Qt::Horizontal) {
        return QVariant();
    }

    switch (section) {
    case StateColumn:
        return tr("State");
    case SNRColumn:
        return tr("SNR");
    case NameColumn:
        return tr("Name");
    default:
        return QVariant();
    }
}

QVariant BeaconListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    const int row = index.row();
    if (row >= QEnvironement::instance()->beaconsCount() || row < 0) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    const int column = index.column();
    const QBeacon beacon = QEnvironement::instance()->beacon(row);
    if (column == StateColumn && role == Qt::DecorationRole) {
        return QVariant::fromValue<QIcon>(SIGNAL_OFF_ICON);
    } else if (column == SNRColumn && role == Qt::DisplayRole) {
        return QVariant::fromValue<QString>(QString::number(beacon->SNR()));
    } else if (column == NameColumn && role == Qt::DisplayRole) {
        return QVariant::fromValue<QString>(beacon->name());
    } else if (role == Qt::UserRole) {
        return QVariant::fromValue<QBeacon>(beacon);
    } else {
        return QVariant();
    }
}


