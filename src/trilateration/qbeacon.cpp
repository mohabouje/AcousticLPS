#include "qbeacon.h"
#include <QDebug>
QBeacon::QBeacon() {

}

QBeacon::QBeacon(const QBeacon &beacon) {
    _identifier = beacon._identifier;
    _position = beacon._position;
    _uuid = beacon._uuid;
    _name = beacon._name;
}

QBeacon::~QBeacon() {

}

QBeacon QBeacon::createBeacon(const Point &position, int identifier) {
    QBeacon beacon;
    beacon.setUniversalUniqueIdentifier(QUuid::createUuid());
    beacon.setPosition(position);
    beacon.setIdentifier(identifier);
    return beacon;
}


void QBeacon::setPosition(const Point &point) {
    _position = point;
}

void QBeacon::setUniversalUniqueIdentifier(const QUuid &uuid) {
    Q_ASSERT_X(!uuid.isNull(), __FUNCTION__, "Error: trying to set a null uuid");
    _uuid = uuid;
}

void QBeacon::setIdentifier(int id) {
    Q_ASSERT_X(id > -1, __FUNCTION__, "Error: trying to set a negative identifier");
    _identifier = id;
}

void QBeacon::setName(const QString &name) {
    _name = name;
}

void QBeacon::setSNR(const Real &SNR) {
    _SNR = SNR;
}
