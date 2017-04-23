#include "qtrilateration.h"
#include <functional>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

QTrilateration::QTrilateration() :
    Trilateration()
{

}

QTrilateration::Error QTrilateration::calculatePosition() const {
    return NoError;
}

QPointF QTrilateration::estimatedPosition() const {
    return _estimatedPosition;
}

void QTrilateration::setBeacons(const QSet<QBeacon> &beacons) {
    _beacons = beacons;
}

void QTrilateration::setMeasures(const QVector<QMeasure> &measures) {
    Q_ASSERT_X(_beacons.isEmpty(), __FUNCTION__, "Error: no beacons was setted yet.");
    // TODO: implement filter unknown beacons.
    _measures = measures;
}

inline bool operator ==(QBeacon& a, QBeacon& b) {
    return a.identifier() == b.identifier()
            && a.position() == b.position()
            && a.universalUniqueIdentifier() == b.universalUniqueIdentifier();
}
inline

QTrilateration::Error QTrilateration::removeDuplicatedMeasures() {
    if (_measures.isEmpty() || _beacons.isEmpty()) {
        return EmptyBufferData;
    }

    foreach (const QBeacon& beacon, _beacons) {
        double distance = 0.0, rssi = 0.0;
       const int measureCount = std::count_if(_measures.begin(), _measures.end(), [&](const QMeasure& measure){
            const bool equal = (*measure.getBeacon() == beacon);
            if (equal) {
                distance += measure.getMeasure();
                rssi += measure.getRSSI();
            }
            return equal;
        });
        if (measureCount > 1) {
            distance /= measureCount;
            rssi /= measureCount;

            auto comparator = [beacon](const QMeasure& measure) {
                return beacon == *measure.getBeacon();
            };

            QVector<QMeasure>::iterator iterator = std::find_if(_measures.begin(), _measures.end(), comparator);
            iterator->setMeasure(distance);
            iterator->setRSSI(rssi);

            iterator = std::remove_if(iterator, _measures.end(), comparator);
            _measures.erase(iterator, _measures.end());
        }
    }
    return NoError;
}
