#include "qmeasure.h"

QMeasure::QMeasure() {
}

QMeasure QMeasure::createMeasure(const QBeacon *beacon, double distance, double rssi) {
    QMeasure measure;
    measure.setBeacon(beacon);
    measure.setMeasure(distance);
    measure.setRSSI(rssi);
    return measure;
}

void QMeasure::setBeacon(const QBeacon *beacon) {
    Q_ASSERT_X(beacon, __FUNCTION__, "Error: null ptr for measure");
    _beacon = beacon;
}

void QMeasure::setMeasure(Real measure) {
    Q_ASSERT_X(measure > 0, __FUNCTION__, "Error: negative measure estimated");
    _measure = measure;
}

void QMeasure::setRSSI(Real rssi) {
    _rssi = rssi;
}
