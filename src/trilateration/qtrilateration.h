#ifndef QTRILATERATION_H
#define QTRILATERATION_H

#include "qbeacon.h"
#include "qmeasure.h"

#include <QSet>
#include <QVector>

class QTrilateration  {
public:
    enum Error { NoError = 0, EmptyMeasures, EmptyBeacons, NotEnoughtMeasure, NotSolution, Unknown };
    enum CartesianCoordinates { AxisX = 0, AxisY, AxisZ, AxisCount };
    enum Algorithm { LinearLeastSquares = 0, NonLinearLeastSquares };
    static constexpr int MinimumRequiredMeasures{4};

    QTrilateration();
    inline Point   estimatedPosition() const { return _estimatedPosition; }
    inline const QSet<QBeacon> beacons() const { return _beacons; }
    inline const QVector<QMeasure> measures() const { return _measures; }

    Error   calculatePosition(Algorithm algorithm = LinearLeastSquares);
    void clear();
    void setBeacons(const QSet<QBeacon> &beacons);
    bool setMeasures(const QVector<QMeasure> &measures);
private:
    Point             _estimatedPosition;
    QSet<QBeacon>       _beacons;
    QVector<QMeasure>   _measures;

    bool removeMeasuresFromUnknownBeacon();
    bool removeDuplicatedMeasures();
    QTrilateration::Error solveNonLinearLeastSquares();
    QTrilateration::Error solveLinearLeastSquares();
};

#endif // QTRILATERATION_H
