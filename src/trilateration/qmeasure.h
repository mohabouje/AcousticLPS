#ifndef QMEASURE_H
#define QMEASURE_H

#include "qbeacon.h"
class QMeasure {
public:
    QMeasure();
    static QMeasure createMeasure(QBeacon* beacon, double distance, double rssi);
    inline QBeacon *getBeacon() const { return _beacon; }
    inline double getMeasure() const { return _measure; }
    inline double getRSSI() const { return _rssi; }
    inline bool operator<(const QMeasure& entry) const {
        return _measure < entry._measure;
    }
    inline bool operator>(const QMeasure& entry) const {
        return !(*this < entry);
    }
    inline bool operator==(const QMeasure& entry) const {
        return (*_beacon == *entry._beacon)
                && _measure == entry._measure
                && _rssi == entry._rssi;
    }
    inline bool operator!=(const QMeasure& entry) const {
        return !(*this == entry);
    }
    void setBeacon(QBeacon *beacon);
    void setMeasure(double measure);
    void setRSSI(double rssi);
private:
    QBeacon*    _beacon;
    double      _measure;
    double      _rssi;
};

inline uint qHash(const QMeasure &f) {
    return qHash(f.getBeacon()->universalUniqueIdentifier());
}
#endif // QMEASURE_H
