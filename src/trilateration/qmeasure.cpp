#include "qmeasure.h"

QMeasure::QMeasure() :
    BeaconMeas()
{

}

double QMeasure::getMeasure() const {
    return BeaconMeas::getDistance();
}

double QMeasure::getRSSI() const {
    return BeaconMeas::getRssi();
}

QBeacon *QMeasure::getBeacon() const {
    return _beacon;
}

void QMeasure::setBeacon(QBeacon *beacon) {
    Q_ASSERT_X(beacon, __FUNCTION__, "Error: null ptr for measure");
    BeaconMeas::setBeaconPtr(beacon);
    BeaconMeas::setBeaconId(beacon->universalUniqueIdentifier().toString().toStdString());
    _beacon = beacon;
}

void QMeasure::setMeasure(double measure) {
    Q_ASSERT_X(measure > 0, __FUNCTION__, "Error: negative measure estimated");
    BeaconMeas::setDistance(measure);
}

void QMeasure::setRSSI(double rssi) {
    BeaconMeas::setRssi(rssi);
}
