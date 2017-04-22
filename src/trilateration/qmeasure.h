#ifndef QMEASURE_H
#define QMEASURE_H

#include "qbeacon.h"

class QMeasure : public BeaconMeas
{
public:
    QMeasure();
    static QMeasure createMeasure(QBeacon* beacon, double distance, double rssi);
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
