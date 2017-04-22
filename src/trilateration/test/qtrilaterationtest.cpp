#include <trilateration/qbeacon.h>
#include <trilateration/qtrilateration.h>

#include <QSignalSpy>
#include <catch.hpp>

SCENARIO("Testing the trilateration algorithm", "[QTrilateration]") {
    GIVEN("A set of beacons") {
        const QVector<QPoint> fixedPosition = {
            QPoint(54.69, 29.51),
            QPoint(54.68, 29.51),
            QPoint(49.05, 32.16)
        };

        QVector<QBeacon> beacons;
        const int size = fixedPosition.size();
        for (int i=0; i<size; i++) {
            beacons.append(QBeacon::createBeacon(fixedPosition[i], i));
        }
        QTrilateration* trilateration = new QTrilateration(Q_NULLPTR);
    }
}
