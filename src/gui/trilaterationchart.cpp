#include "trilaterationchart.h"
#include <model/qenvironement.h>
#include <math/mathutil.h>
#include <qwt_symbol.h>

TrilaterationChart::TrilaterationChart(QWidget* parent) : BeaconsChart(parent) {
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

void TrilaterationChart::setMeasures(const QVector<QMeasure> &measures) {
    _measures = measures;
    repaintTrilateration();
}

static inline QVector<QMeasure> discardMeasuredFromDisabledBeacons(const QVector<QMeasure> &measures) {
    QVector<QMeasure> fixed;
    foreach (const QMeasure& measure, measures) {
        if (measure.getBeacon()->isEnabled()) {
            fixed.append(measure);
        }
    }
    return fixed;
}

static constexpr Size HyperbolicSize = 200;
void TrilaterationChart::repaintTrilateration() {
    const QVector<QMeasure> measures = discardMeasuredFromDisabledBeacons(_measures);
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


void TrilaterationChart::showGrid(bool show) {
    showChart(_grid, show);
    replot();
}

void TrilaterationChart::showTrilateration(bool show) {
    showChart(_trilaterationCurve, show);
    replot();
}

