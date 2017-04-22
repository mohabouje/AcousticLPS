#ifndef QBEACON_H
#define QBEACON_H

#include <QObject>
#include <QPoint>
#include <QUuid>
#include <beacon.h>

class QBeacon : public QObject, Beacon {
    Q_OBJECT
public:
    explicit QBeacon(QObject *parent = 0);
    QUuid universalUniqueIdentifier() const;
    QPoint position() const;
    int identifier() const;
public slots:
    void setPosition(const QPoint& point);
    void setUniversalUniqueIdentifier(const QUuid& uuid);
    void setIdentifier(int id);
signals:
    void onUniversallyUniqueIdentifierChanged(const QUuid& uuid) const;
    void onIdentifierChanged(int id) const;
    void onPositionChanged(const QPoint& point) const;
};

#endif // QBEACON_H
