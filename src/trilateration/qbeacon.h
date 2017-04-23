#ifndef QBEACON_H
#define QBEACON_H

#include <QUuid>
#include <armadillo>
typedef arma::vec::fixed<3> Point;
class QBeacon {
public:
    QBeacon();
    static QBeacon createBeacon(const Point& position, int identifier = 0);
    inline Point position() const { return _position; }
    inline QUuid universalUniqueIdentifier() const { return _uuid; }
    inline int identifier() const { return _identifier; }
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
private:
    Point         _position;
    QUuid           _uuid;
    int             _identifier;
};

inline bool operator ==(const Point& a, const Point& b) {
    return a(0) == b(0) && a(1) == b(1) && a(2) == b(2);
}

inline uint qHash(const QBeacon &f) {
    return qHash(f.universalUniqueIdentifier());
}

#endif // QBEACON_H
