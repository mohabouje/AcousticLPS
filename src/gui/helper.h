#ifndef HELPER_H
#define HELPER_H

#include <trilateration/qbeacon.h>
#include <trilateration/qmeasure.h>
#include <QModelIndex>

namespace Gui {
    inline QBeacon qBeaconFromQModelIndex(const QModelIndex& index) {
        const QVariant data = index.data(Qt::UserRole);
        return data.canConvert<QBeacon>() ? data.value<QBeacon>() : QBeacon();
    }
}

#endif // HELPER_H
