#include "beaconschart.h"

#include <model/qenvironement.h>

#include <qwt_symbol.h>
#include <qwt_picker_machine.h>
#include <qwt_scale_widget.h>
#include <QDebug>
#include <QLabel>
#include <QEvent>

BeaconsChart::BeaconsChart(QWidget* parent) : QwtPlot(parent) {

    QwtSymbol* disabledSymbol = new QwtSymbol;
    disabledSymbol->setStyle(QwtSymbol::Ellipse);
    disabledSymbol->setPen(Qt::black);
    disabledSymbol->setBrush(QBrush(Qt::gray));
    disabledSymbol->setSize(QSize(15, 15));
    _disabledBeacons->setSymbol(disabledSymbol);
    _disabledBeacons->setStyle(QwtPlotCurve::NoCurve);
    _disabledBeacons->attach(this);

    QwtSymbol* enabledSymbol = new QwtSymbol;
    enabledSymbol->setStyle(QwtSymbol::Ellipse);
    enabledSymbol->setPen(Qt::black);
    enabledSymbol->setBrush(QBrush(Qt::cyan));
    enabledSymbol->setSize(QSize(15, 15));
    _enabledBeacons->setSymbol(enabledSymbol);
    _enabledBeacons->setStyle(QwtPlotCurve::NoCurve);
    _enabledBeacons->attach(this);


    QwtSymbol* selectedSymbol = new QwtSymbol;
    selectedSymbol->setStyle(QwtSymbol::Ellipse);
    selectedSymbol->setPen(Qt::black);
    selectedSymbol->setBrush(QBrush(Qt::red));
    selectedSymbol->setSize(QSize(15, 15));
    _selectedBeacons->setSymbol(selectedSymbol);
    _selectedBeacons->setStyle(QwtPlotCurve::NoCurve);
    _selectedBeacons->attach(this);

    BeaconPicker* picker = new BeaconPicker(QwtPlot::xBottom, QwtPlot::yLeft,
                                              QwtPlotPicker::EllipseRubberBand, QwtPicker::AlwaysOn,
                                              this->canvas());
    picker->setStateMachine(new QwtPickerClickPointMachine);
    picker->setRubberBandPen(QColor(Qt::green));
    picker->setTrackerPen(QColor(Qt::blue));
    picker->setTrackerFont(this->font());

    setAxisAutoScale(QwtPlot::xBottom, false);
    setAxisAutoScale(QwtPlot::yLeft, false);

    setAxisScale(QwtPlot::xBottom, 0, Environement->width());
    setAxisScale(QwtPlot::yLeft, 0, Environement->width());

    QFrame* frame = qobject_cast<QFrame*>(canvas());
    frame->setFrameStyle(QFrame::StyledPanel);
}

void BeaconsChart::beaconSelected(const QBeacon &beacon) {
    _beacon = beacon;
    repaintBeacons();
}

void BeaconsChart::updateEnvironement() {
    setAxisScale(QwtPlot::xBottom, 0, Environement->width());
    setAxisScale(QwtPlot::yLeft, 0, Environement->width());
}

void BeaconsChart::repaintBeacons() {
    const Size N = Environement->beaconsCount();
    QVector<Real> xEnabled, yEnabled, xDisabled, yDisabled, xSelected, ySelected;
    for (Size i=0; i<N; i++) {
        const QBeacon beacon = Environement->beaconAt(i);
        const Position point = beacon->position();
        if (beacon == _beacon) {
            xSelected.append(point(0));
            ySelected.append(point(1));
        } else if (beacon->isEnabled()) {
            xEnabled.append(point(0));
            yEnabled.append(point(1));
        } else {
            xDisabled.append(point(0));
            yDisabled.append(point(1));
        }
    }
    _enabledBeacons->setSamples(xEnabled, yEnabled);
    _disabledBeacons->setSamples(xDisabled, yDisabled);
    _selectedBeacons->setSamples(xSelected, ySelected);
    if (isVisible()) {
        replot();
    }
}

void BeaconsChart::showBeacons(bool show) {
    showChart(_enabledBeacons, show);
    showChart(_disabledBeacons, show);
    showChart(_selectedBeacons, show);
    if (isVisible()) {
        replot();
    }
}

void BeaconsChart::showAxis(bool state) {
    enableAxis(QwtPlot::xBottom, state);
    enableAxis(QwtPlot::yLeft, state);
}

void BeaconsChart::showChart(QwtPlotItem *curve, bool state) {
    if (state) {
        curve->attach(this);
    } else {
        curve->detach();
    }
}

BeaconPicker::BeaconPicker(int xAxis, int yAxis, RubberBand rubberBand, DisplayMode trackerMode, QWidget* canvas)
    : QwtPlotPicker(xAxis, yAxis, rubberBand, trackerMode, canvas)
{

}
QwtText BeaconPicker::trackerTextF(const QPointF &pos) const {
    return QwtText(QString("(%1,%2)").arg(QString::number(pos.x(), 'd', 2)).arg(QString::number(pos.y(), 'd', 2)));
}



