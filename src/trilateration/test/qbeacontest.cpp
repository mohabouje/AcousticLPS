#include <trilateration/qbeacon.h>

#include <QSignalSpy>
#include <catch.hpp>
SCENARIO( "Testing the correct behaviour of a beacon", "[QBeacon]" ) {
    GIVEN("A beacon with some properties") {
        QBeacon* beacon = new QBeacon(Q_NULLPTR);
        WHEN("We set up a generic QUuid") {
            QSignalSpy onUuidChanged(beacon, &QBeacon::onUniversallyUniqueIdentifierChanged);
            const QUuid test = QUuid::createUuid();
            beacon->setUniversalUniqueIdentifier(test);
            THEN("it should be changed to the same") {
                REQUIRE(beacon->universalUniqueIdentifier() == test);
            }
            AND_THEN("the notify signal should be emitted") {
                REQUIRE(onUuidChanged.count() > 0);
            }
        }
        WHEN("We set up a generic identifier") {
            QSignalSpy onIdentifierChanged(beacon, &QBeacon::onIdentifierChanged);
            const int identifier = qrand();
            beacon->setIdentifier(identifier);
            THEN("it should be changed to the same") {
                REQUIRE(beacon->identifier() == identifier);
            }
            AND_THEN("the notify signal should be emitted") {
                REQUIRE(onIdentifierChanged.count() > 0);
            }
        }
        WHEN("We set up a generic position") {
            QSignalSpy onPositionChanged(beacon, &QBeacon::onPositionChanged);
            const QPoint point(qrand(), qrand());
            beacon->setPosition(point);
            THEN("it should be changed to the same") {
                REQUIRE(beacon->position() == point);
            }
            AND_THEN("the notify signal should be emitted") {
                REQUIRE(onPositionChanged.count() > 0);
            }
        }
    }
}

