#ifndef QMEASURE_H
#define QMEASURE_H
#include "config.h"
#include "qbeacon.h"
#include <QMetaType>
class QMeasure {
public:
    QMeasure();
    QMeasure(const QMeasure& measure);
    ~QMeasure();
    static QMeasure createMeasure(const QBeacon* beacon, double distance, double rssi);
    inline const QBeacon *getBeacon() const { return _beacon; }
    inline Real getMeasure() const { return _measure; }
    inline Real getRSSI() const { return _rssi; }
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
    void setBeacon(const QBeacon *beacon);
    void setMeasure(Real measure);
    void setRSSI(Real rssi);
private:
    const QBeacon*          _beacon;
    Real                    _measure;
    Real                    _rssi;
};

Q_DECLARE_METATYPE(QMeasure)

inline uint qHash(const QMeasure &f) {
    return qHash(f.getBeacon()->universalUniqueIdentifier());
}
#endif // QMEASURE_H
