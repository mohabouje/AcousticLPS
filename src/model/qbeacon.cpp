#include "qbeacon.h"
#include <QDebug>
BeaconWrapper::BeaconWrapper(Beacon* beacon) : _beacon(beacon) {

}

void BeaconWrapper::setPosition(const Position &point) {
    Point* local = _beacon->mutable_point();
    local->set_x(point(0));
    local->set_y(point(1));
    local->set_z(point(2));
}

void BeaconWrapper::setUniversalUniqueIdentifier(const QUuid &uuid) {
    _beacon->set_uuid(uuid.toString().toStdString());
}

void BeaconWrapper::setIdentifier(int id) {
    _beacon->set_id(id);
}

void BeaconWrapper::setName(const QString &name) {
    _beacon->set_name(name.toStdString());
}

void BeaconWrapper::setSNR(const Real &SNR) {
    _beacon->set_snr(SNR);
}
