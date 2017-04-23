#include "qtrilateration.h"
#include <armadillo>
using namespace arma;
#include <QDebug>
QTrilateration::QTrilateration()
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

    return [&, algorithm]() {
        switch (algorithm) {
        case LinearLeastSquares:
            return solveLinearLeastSquares();
        case SingularValueDecomposition:
            return solveSingularValueDecomposition();
        case NonLinearLeastSquares:
            return solveNonLinearLeastSquares();
        default:
            return Unknown;
        }
    }();
}


QTrilateration::Error QTrilateration::solveLinearLeastSquares() const {
    mat A(5, 5, fill::randu);
    double x = A(1,2);

    mat B = A + A;
    mat C = A * B;
    mat D = A % B;

    cx_mat X(A,B);

    B.zeros();
    B.set_size(10,10);
    B.ones(5,6);

    B.print("B:");

    mat::fixed<5,6> F;

    double aux_mem[24];
    mat H(&aux_mem[0], 4, 6, false);  // use auxiliary memory


    return NoError;
}
QTrilateration::Error QTrilateration::solveSingularValueDecomposition() const {
    return NoError;
}
QTrilateration::Error QTrilateration::solveNonLinearLeastSquares() const {
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
