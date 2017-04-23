#ifndef QTRILATERATION_H
#define QTRILATERATION_H

#include "qbeacon.h"
#include "qmeasure.h"

#include <QSet>
#include <QVector>

class QTrilateration  {
public:
    enum Error {
        NoError = 0,
        EmptyMeasures,
        EmptyBeacons,
        NotEnoughtMeasure,
        InvalidSolution,
        Unknown
    };

    enum Algorithm {
        LinearLeastSquares = 0,
        SingularValueDecomposition,
        NonLinearLeastSquares
    };

    enum CartesianCoordinates {
        AxisX = 0,
        AxisY,
        AxisZ,
        AxisCount
    };

    QTrilateration();
    void clear();

    Error   calculatePosition(Algorithm algorithm = LinearLeastSquares) const;
    Point   estimatedPosition() const;

    void setBeacons(const QSet<QBeacon> &beacons);
    void setMeasures(const QVector<QMeasure> &measures);

private:
    Point             _estimatedPosition;
    QSet<QBeacon>       _beacons;
    QVector<QMeasure>   _measures;

    static constexpr int MinimumRequiredMeasures{4};
    static constexpr double DefaultHeight{0.0};

    bool removeMeasuresFromUnknownBeacon();
    bool removeDuplicatedMeasures();
    QTrilateration::Error solveNonLinearLeastSquares() const;
    QTrilateration::Error solveSingularValueDecomposition() const;
    QTrilateration::Error solveLinearLeastSquares() const;
};

#endif // QTRILATERATION_H
