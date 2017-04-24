#ifndef QBEACON_H
#define QBEACON_H
#include "config.h"
#include <QMetaType>
#include <QUuid>
class QBeacon {
public:
    QBeacon();
    QBeacon(const QBeacon& beacon);
    ~QBeacon();
    static QBeacon createBeacon(const Point& position, int identifier = 0);
    inline Point position() const { return _position; }
    inline QUuid universalUniqueIdentifier() const { return _uuid; }
    inline int identifier() const { return _identifier; }
    inline QString name() const { return _name; }
    inline Real SNR() const { return _SNR; }
    inline bool operator==(const QBeacon& beacon) const {
        return _identifier == beacon._identifier
                && _uuid == beacon._uuid;
    }
    inline bool operator!=(const QBeacon& beacon) const {
        return !(*this == beacon);
    }
    inline bool operator<(const QBeacon& beacon) const {
        return _identifier < beacon._identifier
                || _uuid < beacon._uuid;
    }
    inline bool operator>(const QBeacon& beacon) const {
        return !(*this < beacon);
    }
    void setPosition(const Point& point);
    void setUniversalUniqueIdentifier(const QUuid& uuid);
    void setIdentifier(int id);
    void setName(const QString &name);
    void setSNR(const Real &SNR);

private:
    Point           _position{0,0,0};
    QUuid           _uuid;
    int             _identifier{0};
    Real            _SNR{0};
    QString         _name;
};
Q_DECLARE_METATYPE(QBeacon)

inline bool operator ==(const Point& a, const Point& b) {
    return a(0) == b(0) && a(1) == b(1) && a(2) == b(2);
}

inline uint qHash(const QBeacon &f) {
    return qHash(f.universalUniqueIdentifier());
}

#endif // QBEACON_H
