#include "qtrilateration.h"
#include <functional>
#include <iostream>
#include <algorithm>
#include <cctype>

#include <QDebug>

QTrilateration::QTrilateration() :
    Trilateration()
{

}

void QTrilateration::clear() {
    _beacons.clear();
    _measures.clear();
}

QTrilateration::Error QTrilateration::calculatePosition(QTrilateration::Algorithm algorithm) const {
    if (_beacons.isEmpty()) return EmptyBeacons;
    if (_measures.isEmpty()) return EmptyMeasures;
    if (_measures.size() < MinimumRequiredMeasures) return NotEnoughtMeasure;


    return NoError;
}

QPointF QTrilateration::estimatedPosition() const {
    return _estimatedPosition;
}

void QTrilateration::setBeacons(const QSet<QBeacon> &beacons) {
    _beacons = beacons;
}

void QTrilateration::setMeasures(const QVector<QMeasure> &measures) {
    _measures = measures;
    const bool removed = removeMeasuresFromUnknownBeacon();
    if (removed) {
        qWarning() << "Warning: got measures from unknown beacons";
    }
    const bool duplicated = removeDuplicatedMeasures();
    if (duplicated) {
        qWarning() << "Warning: got different measures for the same beacon";
    }
}

inline bool operator ==(QBeacon& a, QBeacon& b) {
    return a.identifier() == b.identifier()
            && a.position() == b.position()
            && a.universalUniqueIdentifier() == b.universalUniqueIdentifier();
}

bool QTrilateration::removeMeasuresFromUnknownBeacon() {
    auto iterator = std::remove_if(_measures.begin(), _measures.end(), [&](const QMeasure& measure){
        const QBeacon beacon = *measure.getBeacon();
        return !_beacons.contains(beacon);
    });
    const bool somethingRemoved = iterator != _measures.end();
    _measures.erase(iterator, _measures.end());
    return somethingRemoved;
}


bool QTrilateration::removeDuplicatedMeasures() {
    bool duplicated = false;
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
            duplicated = true;
            distance /= measureCount;
            rssi /= measureCount;

            static auto comparator = [beacon](const QMeasure& measure) {
                return beacon == *measure.getBeacon();
            };

            QVector<QMeasure>::iterator iterator = std::find_if(_measures.begin(), _measures.end(), comparator);
            iterator->setMeasure(distance);
            iterator->setRSSI(rssi);

            iterator = std::remove_if(iterator, _measures.end(), comparator);
            _measures.erase(iterator, _measures.end());
        }
    }
    return duplicated;
}
