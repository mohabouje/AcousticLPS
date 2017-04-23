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
        EmptyBufferData,
        InvalidBeacon,
        NotFound
    };

    QTrilateration();
    void clear();

    Error   calculatePosition() const;
    QPointF estimatedPosition() const;

    void setBeacons(const QSet<QBeacon> &beacons);
    void setMeasures(const QVector<QMeasure> &measures);

private:
    QPointF         _estimatedPosition;
    QSet<QBeacon>   _beacons;
    QVector<QMeasure>  _measures;

    Error removeDuplicatedMeasures();
    bool removeMeasuresFromUnknownBeacon();
};

#endif // QTRILATERATION_H
