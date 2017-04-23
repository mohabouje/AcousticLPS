#ifndef QTRILATERATION_H
#define QTRILATERATION_H

#include "qbeacon.h"
#include "qmeasure.h"

#include <QSet>
#include <QVector>
#include <trilateration.h>

class QTrilateration : public Trilateration
{
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

    QTrilateration();
    void clear();

    Error   calculatePosition(Algorithm algorithm = LinearLeastSquares) const;
    QPointF estimatedPosition() const;

    void setBeacons(const QSet<QBeacon> &beacons);
    void setMeasures(const QVector<QMeasure> &measures);

private:
    QPointF             _estimatedPosition;
    QSet<QBeacon>       _beacons;
    QVector<QMeasure>   _measures;

    static const int MinimumRequiredMeasures{3};

    bool removeMeasuresFromUnknownBeacon();
    bool removeDuplicatedMeasures();
    QTrilateration::Error solveNonLinearLeastSquares() const;
    QTrilateration::Error solveSingularValueDecomposition() const;
    QTrilateration::Error solveLinearLeastSquares() const;
};

#endif // QTRILATERATION_H
