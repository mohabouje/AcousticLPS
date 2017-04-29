#include "routeschart.h"
#include <model/qenvironement.h>
#include <math/mathutil.h>
#include <qwt_symbol.h>

RoutesChart::RoutesChart(QWidget* parent) : BeaconsChart(parent) {
    _grid->enableXMin(true);
    _grid->enableYMin(true);
    _grid->setMajorPen(QPen(Qt::black, 0, Qt::DotLine));
    _grid->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
    _grid->attach(this);

    QwtSymbol* selectedSymbol = new QwtSymbol;
    selectedSymbol->setStyle(QwtSymbol::Ellipse);
    selectedSymbol->setBrush(QBrush(Qt::red));
    _trilaterationCurve->setStyle(QwtPlotCurve::NoCurve);
    _trilaterationCurve->setSymbol(selectedSymbol);
    _trilaterationCurve->attach(this);

    updateEnvironement();
    repaintBeacons();
}

inline QVector<QMeasure> avoidDisabledBeacons(const QVector<QMeasure> &measures) {
    QVector<QMeasure> fixed;
    foreach (const QMeasure& measure, measures) {
        if (measure.getBeacon()->isEnabled()) {
            fixed.append(measure);
        }
    }
    return fixed;
}

void RoutesChart::estimateRoute(const QVector<QMeasure> &input) {
    static constexpr Size HyperbolicSize = 200;
    const QSet<QBeacon>& beacons = QEnvironementInstance->beacons();
    const QVector<QMeasure> measures = avoidDisabledBeacons(input);

    _trilateration->setBeacons(beacons);
    _trilateration->setMeasures(measures);
    _trilateration->calculatePosition();

    const Size N = measures.size();
    const Size total = N * HyperbolicSize;
    QwtData trilaterationData = QwtData(total);
    for (Size i=0; i<N; i++) {
        const QBeacon& beacon = measures[i].getBeacon();
        const QwtData hyperbolic = MathUtil::hiperbolicChart(beacon->position(), measures[i].getMeasure(), HyperbolicSize);
        for (Size j=0; j<HyperbolicSize; j++) {
            trilaterationData.xData(i*HyperbolicSize + j) = hyperbolic.xData(j);
            trilaterationData.yData(i*HyperbolicSize + j) = hyperbolic.yData(j);
        }
    }
    _trilaterationCurve->setSamples(trilaterationData.x(), trilaterationData.y(), trilaterationData.size());
    replot();
}


void RoutesChart::showGrid(bool show) {
    showChart(_grid, show);
    replot();
}

void RoutesChart::showTrilateration(bool show) {
    showChart(_trilaterationCurve, show);
    replot();
}

