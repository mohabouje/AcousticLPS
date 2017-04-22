#include "qbeacon.h"

QBeacon::QBeacon(QObject *parent) :
    QObject(parent),
    Beacon()
{

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
    emit onPositionChanged(point);
}

void QBeacon::setUniversalUniqueIdentifier(const QUuid &uuid) {
    const std::string tmp = uuid.toString().toStdString();
    Beacon::setBeaconId(tmp);
    emit onUniversallyUniqueIdentifierChanged(uuid);
}

void QBeacon::setIdentifier(int id) {
    Beacon::setLocationId(id);
    emit onIdentifierChanged(id);
}

