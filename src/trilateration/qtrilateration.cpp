#include "qtrilateration.h"

#include <ceres/ceres.h>
#include <ceres/solver.h>
#include <QDebug>
QTrilateration::QTrilateration()
{

}

void QTrilateration::clear() {
    _beacons.clear();
    _measures.clear();
}

QTrilateration::Error QTrilateration::calculatePosition(QTrilateration::Algorithm algorithm) {
    if (_beacons.isEmpty()) return EmptyBeacons;
    if (_measures.isEmpty()) return EmptyMeasures;

    return [&, algorithm]() {
        switch (algorithm) {
        case LinearLeastSquares:
            return solveLinearLeastSquares();
        case NonLinearLeastSquares:
            return solveNonLinearLeastSquares();
        default:
            return Unknown;
        }
    }();
}


QTrilateration::Error QTrilateration::solveLinearLeastSquares() {
    const int measureCount = _measures.size();
    if (measureCount < MinimumRequiredMeasures) {
        qWarning() << "Not enought measures to use this algorithm.";
        return NotEnoughtMeasure;
    }

    const int equationCount = measureCount - 1;
    const QMeasure& first = _measures.first();
    const Real refDistance = first.getMeasure();
    const Point constraint = first.getBeacon()->position();

    Matrix A(equationCount, AxisCount);
    Vector b(equationCount);
    for (int i=0; i<equationCount; i++) {
        const Point u = _measures[i+1].getBeacon()->position() - constraint;
        Real d = 0.0;
        for (int j=AxisX; j<AxisCount; j++) {
            Real diff = u(j);
            A(i,j) = diff;
            d += (diff *= diff);
        }
        const Real distance = _measures[i+1].getMeasure();
        b(i) = 0.5 * (refDistance*refDistance - distance*distance + d);
    }

    Vector solution;
    const bool findSolution = arma::solve(solution, A, b) ;
    for (int i=AxisX; i<AxisCount; i++) {
        _estimatedPosition(i) = solution(i);
    }
    _estimatedPosition += constraint;
    return findSolution ? NoError : NotSolution;
}

QTrilateration::Error QTrilateration::solveNonLinearLeastSquares() {
    ceres::Solver::Options options;
    ceres::Solver::Summary summary;

    return NoError;
}




void QTrilateration::setBeacons(const QSet<QBeacon> &beacons) {
    _beacons = beacons;
}

bool QTrilateration::setMeasures(const QVector<QMeasure> &measures) {
    _measures = measures;
    const bool removed = removeMeasuresFromUnknownBeacon();
    const bool duplicated = removeDuplicatedMeasures();
    return removed || duplicated;
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
