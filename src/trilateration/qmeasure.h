#ifndef QMEASURE_H
#define QMEASURE_H

#include "qbeacon.h"

class QMeasure : private BeaconMeas
{
public:
    QMeasure();
    void setBeacon(QBeacon *beacon);
    QBeacon *getBeacon() const;

    void setMeasure(double measure);
    double getMeasure() const;

    void setRSSI(double rssi);
    double getRSSI() const;
private:
    QBeacon*    _beacon;
};

#endif // QMEASURE_H
