#include "qbeacon.h"

QBeacon::QBeacon() :
    Beacon()
{

}

QBeacon QBeacon::createBeacon(const QPoint &position, int identifier) {
    QBeacon beacon;
    beacon.setUniversalUniqueIdentifier(QUuid::createUuid());
    beacon.setPosition(position);
    beacon.setIdentifier(identifier);
    return beacon;
}

QUuid QBeacon::universalUniqueIdentifier() const {
    const QString tmp = QString::fromStdString(Beacon::getId());
    return QUuid(tmp);
}

QPoint QBeacon::position() const {
    return QPoint(Beacon::getX(), Beacon::getY());
}

int QBeacon::identifier() const {
    return Beacon::getLocationId();
}

void QBeacon::setPosition(const QPoint &point) {
    Beacon::setX(point.x());
    Beacon::setY(point.y());
}

void QBeacon::setUniversalUniqueIdentifier(const QUuid &uuid) {
    Q_ASSERT_X(!uuid.isNull(), __FUNCTION__, "Error: trying to set a null uuid");
    const std::string tmp = uuid.toString().toStdString();
    Beacon::setBeaconId(tmp);
}

void QBeacon::setIdentifier(int id) {
    Q_ASSERT_X(id > -1, __FUNCTION__, "Error: trying to set a negative identifier");
    Beacon::setLocationId(id);
}

