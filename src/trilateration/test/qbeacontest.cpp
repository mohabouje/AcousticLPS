#include <trilateration/qbeacon.h>

#include <QSignalSpy>
#include <catch.hpp>
SCENARIO( "Testing the correct behaviour of a beacon", "[QBeacon]" ) {
    GIVEN("A beacon with some properties") {
        QBeacon beacon;
        WHEN("We set up a generic QUuid") {
            const QUuid test = QUuid::createUuid();
            beacon.setUniversalUniqueIdentifier(test);
            THEN("it should be changed to the same") {
                REQUIRE(beacon.universalUniqueIdentifier() == test);
            }
        }
        WHEN("We set up a generic identifier") {
            const int identifier = qrand();
            beacon.setIdentifier(identifier);
            THEN("it should be changed to the same") {
                REQUIRE(beacon.identifier() == identifier);
            }
        }
        WHEN("We set up a generic position") {
            const QPoint point(qrand(), qrand());
            beacon.setPosition(point);
            THEN("it should be changed to the same") {
                REQUIRE(beacon.position() == point);
            }
        }
    }
}

