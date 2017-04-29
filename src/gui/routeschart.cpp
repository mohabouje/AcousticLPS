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
}

void RoutesChart::estimateRoute(const QVector<QMeasure> &measures) {
    _trilateration->setBeacons(QEnvironementInstance->beacons());
    _trilateration->setMeasures(measures);
    _trilateration->calculatePosition();

    static constexpr Size HyperbolicSize = 200;
    const Size N = measures.size();
    const Size total = N * HyperbolicSize;
    QwtData trilaterationData = QwtData(total);
    for (Size i=0; i<N; i++) {
        const QBeacon& beacon = measures[i].getBeacon();
        const QwtData huyperbolic = MathUtil::hiperbolicChart(beacon->position(), measures[i].getMeasure(), HyperbolicSize);
        for (Size j=0; j<HyperbolicSize; j++) {
            trilaterationData.xData(i*HyperbolicSize + j) = huyperbolic.xData(j);
            trilaterationData.yData(i*HyperbolicSize + j) = huyperbolic.yData(j);
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

