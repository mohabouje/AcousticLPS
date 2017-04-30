#ifndef QTRILATERATION_H
#define QTRILATERATION_H

#include "dsp.h"
#include <model/qbeacon.h>
#include <model/qmeasure.h>

#include <QSet>
#include <QVector>
namespace DSP {
    class Trilateration  {
    public:
        enum Error { NoError = 0, EmptyMeasures, EmptyBeacons, NotEnoughtMeasure, NotSolution, Unknown };
        enum CartesianCoordinates { AxisX = 0, AxisY, AxisZ, AxisCount };
        enum Algorithm { LinearLeastSquares = 0, NonLinearLeastSquares };
        static constexpr int MinimumRequiredMeasures{4};

        Trilateration();
        inline Position  estimatedPosition() const { return _estimatedPosition; }
        inline const QSet<QBeacon> beacons() const { return _beacons; }
        inline const QVector<QMeasure> measures() const { return _measures; }

        Error   calculatePosition(Algorithm algorithm = LinearLeastSquares);
        void clear();
        void setBeacons(const QSet<QBeacon> &beacons);
        bool setMeasures(const QVector<QMeasure> &measures);
    private:
        Position                _estimatedPosition;
        QSet<QBeacon>           _beacons;
        QVector<QMeasure>       _measures;

        bool removeMeasuresFromUnknownBeacon();
        bool removeDuplicatedMeasures();
        Trilateration::Error solveNonLinearLeastSquares();
        Trilateration::Error solveLinearLeastSquares();
    };
}

#endif // QTRILATERATION_H
