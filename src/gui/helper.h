#ifndef HELPER_H
#define HELPER_H

#include <model/qbeacon.h>
#include <model/qmeasure.h>
#include <QModelIndex>
#include <QIcon>

#define SIGNAL_OFF_ICON QIcon(":/resources/icons/antenna_off.png")
#define SIGNAL_ON_ICON QIcon(":/resources/icons/antenna_on.png")
namespace Gui {
    inline QBeacon qBeaconFromQModelIndex(const QModelIndex& index) {
        const QVariant data = index.data(Qt::UserRole);
        return data.canConvert<QBeacon>() ? data.value<QBeacon>() : QBeacon();
    }
}

#endif // HELPER_H
