#include "beaconschart.h"
#include <model/qenvironement.h>
BeaconsChart::BeaconsChart(QWidget* parent) : QwtPlot(parent)
{
    _disabledSymbol->setStyle(QwtSymbol::Ellipse);
    _disabledSymbol->setPen(Qt::black);
    _disabledSymbol->setBrush(QBrush(Qt::gray));
    _disabledSymbol->setSize(QSize(15, 15));
    _disabledBeacons->setStyle(QwtPlotCurve::NoCurve);
    _disabledBeacons->setSymbol(_disabledSymbol);
    _disabledBeacons->attach(this);

    _enabledSymbol->setStyle(QwtSymbol::Ellipse);
    _enabledSymbol->setPen(Qt::black);
    _enabledSymbol->setBrush(QBrush(Qt::cyan));
    _enabledSymbol->setSize(QSize(15, 15));
    _enabledBeacons->setStyle(QwtPlotCurve::NoCurve);
    _enabledBeacons->setSymbol(_enabledSymbol);
    _enabledBeacons->attach(this);

    setAxisAutoScale(QwtPlot::xBottom, false);
    setAxisAutoScale(QwtPlot::yLeft, false);
}

void BeaconsChart::repaintEnvironement() {
    const int N = QEnvironementInstance->beaconsCount();
    QVector<double> xEnabled, yEnabled, xDisabled, yDisabled;
    QPolygonF points;
    for (int i=0; i<N; i++) {
        const QBeacon beacon = QEnvironementInstance->beaconAt(i);
        const Position point = beacon->position();
        if (beacon->isEnabled()) {
            xEnabled.append(point(0));
            yEnabled.append(point(1));
        } else {
            xDisabled.append(point(0));
            yDisabled.append(point(1));
        }
    }
    _enabledBeacons->setSamples(xEnabled, yEnabled);
    _disabledBeacons->setSamples(xDisabled, yDisabled);
    replot();
}
