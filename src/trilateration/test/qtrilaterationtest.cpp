#include <trilateration/qbeacon.h>
#include <trilateration/qmeasure.h>
#include <trilateration/qtrilateration.h>

#include <QDebug>
#include <QVector>
#include <QPair>
#include <catch.hpp>
SCENARIO("Testing the trilateration algorithm", "[QTrilateration]") {
    GIVEN("A set of beacons") {
        const QVector<QPointF> fixedPosition = {
            QPointF(54.69, 29.51),
            QPointF(54.68, 29.51),
            QPointF(49.05, 32.16)
        };

        using DistanceRSSI = QPair<double, double>;
        const QVector<DistanceRSSI> estimatedDistances = {
            DistanceRSSI(4.47, -86.57),
            DistanceRSSI(14.13, -90.80),
            DistanceRSSI(15.85, -86.41)
        };

       /*std::vector<Beacon> beacons;
        std::vector<BeaconMeas> measures;
        const int size = fixedPosition.size();
        for (int i=0; i<size; i++) {
            QBeacon beacon = QBeacon::createBeacon(fixedPosition[i], i);
            QMeasure measure = QMeasure::createMeasure(&beacon, estimatedDistances[i].first, estimatedDistances[i].second);
            beacons.push_back(beacon);
            measures.push_back(measure);
        }
        QTrilateration* trilateration = new QTrilateration();
        trilateration->fillLocationBeacons(beacons);
        trilateration->updateMeasurements(measures);

        WHEN("We stimate the point") {
            int errorCode = trilateration->calculateCoordinates();
            double x = trilateration->getX();
            double y = trilateration->getY();
            THEN("We got no error") {
                REQUIRE(errorCode == 0);
            }
            AND_THEN("The estimated point is:") {

            }
        }*/
    }
}
