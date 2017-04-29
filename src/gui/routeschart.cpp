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

    updateEnvironement();
    repaintEnvironement();
}

void RoutesChart::plotRoute(const QVector<QMeasure> &measures) {
    _trilateration->setMeasures(measures);
    foreach (const QMeasure& measure, measures) {
        traceHyperbolic(measure);
    }
    replot();
}

void RoutesChart::repaintEnvironement() {
    if (_showBeacons) {
        BeaconsChart::repaintEnvironement();
    } else {
        BeaconsChart::clear();
    }
}

void RoutesChart::updateEnvironement() {
    flushTrilaterationCurves();
    const Size N = QEnvironementInstance->beaconsCount();
    QSet<QBeacon> beacons;
    for (Size i=0; i<N; i++) {
        const QBeacon beacon = QEnvironementInstance->beaconAt(i);
        if (beacon->isEnabled()) {
            QwtPlotCurve* curve = new QwtPlotCurve;
            curve->setStyle(QwtPlotCurve::NoCurve);
            curve->attach(this);
            QwtSymbol* selectedSymbol = new QwtSymbol;
            selectedSymbol->setStyle(QwtSymbol::Cross);
            selectedSymbol->setBrush(QBrush(Qt::red));
            curve->setSymbol(selectedSymbol);

            _trilaterationCurves.insert(beacon, curve);
            beacons.insert(beacon);
        }
    }
    _trilateration->setBeacons(beacons);
    replot();
}

void RoutesChart::showBeacons(bool showBeacons) {
    _showBeacons = showBeacons;
    repaintEnvironement();
}

void RoutesChart::showGrid(bool show) {
    if (show) {
        _grid->attach(this);
    } else {
        _grid->detach();
    }
    replot();
}

void RoutesChart::showTrilateration(bool showTrilateration) {
    _showTrilateration = showTrilateration;
}

void RoutesChart::flushTrilaterationCurves(){
    for (QHash<QBeacon, QwtPlotCurve*>::iterator it = _trilaterationCurves.begin();
             it != _trilaterationCurves.end(); it++) {
        it.value()->detach();
    }
    _trilaterationCurves.clear();
}

void RoutesChart::traceHyperbolic(const QMeasure &measure) {
    const QBeacon beacon = measure.getBeacon();
    if (_trilaterationCurves.contains(beacon)) {
        QwtData data = MathUtil::hiperbolicChart(beacon->position(), measure.getMeasure(), 200);
        _trilaterationCurves[beacon]->setSamples(data.x(), data.y(), data.size());
    }
}
