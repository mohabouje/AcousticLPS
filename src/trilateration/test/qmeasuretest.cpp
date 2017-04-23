#include <trilateration/qmeasure.h>
#include <catch.hpp>
SCENARIO( "Testing the correct behaviour of a given measure", "[QMeasure]" ) {
    GIVEN("A measure") {
        QMeasure measure;
        WHEN("We identify the sender beacon & we set up it") {
            const Point pos = {0.0, 1.0, 2.0};
            QBeacon beacon = QBeacon::createBeacon(pos);
            measure.setBeacon(&beacon);
            THEN("it should be changed to the same") {
                REQUIRE(&beacon == measure.getBeacon());
                REQUIRE(beacon.universalUniqueIdentifier() ==
                        measure.getBeacon()->universalUniqueIdentifier());
                REQUIRE(beacon.position() == measure.getBeacon()->position());
            }
        }
        WHEN("We set up a generic measure") {
            const double distance = 50;
            measure.setMeasure(distance);
            THEN("it should be changed to the same") {
                REQUIRE(measure.getMeasure() == distance);
            }
        }
        WHEN("We set up a generic RSSI") {
            const double rssi = qrand();
            measure.setRSSI(rssi);
            THEN("it should be changed to the same") {
                REQUIRE(measure.getRSSI() == rssi);
            }
        }
    }
}
