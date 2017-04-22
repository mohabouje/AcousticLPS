#ifndef QBEACON_H
#define QBEACON_H

#include <QObject>

class QBeacon : public QObject
{
    Q_OBJECT
public:
    explicit QBeacon(QObject *parent = 0);

signals:

public slots:
};

#endif // QBEACON_H