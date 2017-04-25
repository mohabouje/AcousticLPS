#include "qbeacon.h"
#include <QDebug>
QBeacon::QBeacon() {

}

void QBeacon::setPosition(const Position &point) {
    Point* local = _beacon->mutable_point();
    local->set_x(point(0));
    local->set_y(point(1));
    local->set_z(point(2));
}

void QBeacon::setUniversalUniqueIdentifier(const QUuid &uuid) {
    _beacon->set_uuid(uuid.toString().toStdString());
}

void QBeacon::setIdentifier(int id) {
    _beacon->set_id(id);
}

void QBeacon::setName(const QString &name) {
    _beacon->set_name(name.toStdString());
}

void QBeacon::setSNR(const Real &SNR) {
    _beacon->set_snr(SNR);
}
