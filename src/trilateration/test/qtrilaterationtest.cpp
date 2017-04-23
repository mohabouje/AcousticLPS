#include <trilateration/qbeacon.h>
#include <trilateration/qmeasure.h>
#include <trilateration/qtrilateration.h>

#include <QDebug>
#include <QVector>
#include <QPair>
#include <QFile>
#include <QUrl>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <catch.hpp>


static QVector<Point> getBeaconsPosition() {
    QVector<Point> beaconPositions;
    QFile file (":/testdata.txt");
    const bool opened = file.open(QIODevice::ReadOnly);
    if (opened) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            const QString line = in.readLine();
            const QStringList coordinates = line.split("\t");
            Point pos;
            for (int i=QTrilateration::AxisX; i<QTrilateration::AxisCount; i++) {
                pos(i) = QString(coordinates.at(i)).toFloat();
            }
            beaconPositions.append(pos);
        }
    }
    file.close();
    return beaconPositions;
}

static QVector<float> getExperimentalMeasure(const QString& path) {
    QVector<float> measures;
    QFile file (path);
    const bool opened = file.open(QIODevice::ReadOnly);
    if (opened) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            const float line = in.readLine().toFloat();
            measures.append(line);
        }
    }
    file.close();
    return measures;
}

static QVector<QBeacon> getBeacons(const QVector<Point>& points) {
    QVector<QBeacon> beacons;
    const int N = points.size();
    for (int i=0; i<N; i++) {
        beacons.append(QBeacon::createBeacon(points[i], i));
    }
    return beacons;
}

static QVector<QMeasure> getMeasure(const QVector<QBeacon>& beacons, const QVector<float>& distances) {
    QVector<QMeasure> measures;
    const int N = beacons.size();
    for(int i=0; i<N; i++) {
        measures.append(QMeasure::createMeasure(&beacons[i], distances[i], 1.));
    }
    return measures;
}

SCENARIO("Testing the trilateration algorithm", "[QTrilateration]") {
    GIVEN("A set of beacons & experimental measures") {
        const QVector<Point> beaconsPosition = getBeaconsPosition();
        const QVector<float> measuresDistance = getExperimentalMeasure(":/testmeasures_2.txt");
        const QVector<QBeacon> beacons = getBeacons(beaconsPosition);
        const QVector<QMeasure> measures = getMeasure(beacons, measuresDistance);

        REQUIRE(beacons.size() ==  measures.size());
        QTrilateration* trilateration = new QTrilateration();

        WHEN("We set the experimental points") {
            const bool error =  trilateration->setMeasures(measures);
            THEN("No error is returned") {
                REQUIRE(!error);
            }
        }


        WHEN("We wan to estimate the point by using the linear least squares") {
            trilateration->setBeacons(beacons.toList().toSet());
            trilateration->setMeasures(measures);
            QTrilateration::Error errorCode = trilateration->calculatePosition(QTrilateration::LinearLeastSquares);
            THEN("We got no error") {
                REQUIRE(errorCode == QTrilateration::NoError);
            }
            AND_THEN("The estimated point is:") {

            }
        }
    }
}
