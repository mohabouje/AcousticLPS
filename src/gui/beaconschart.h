#ifndef BEACONSCHART_H
#define BEACONSCHART_H

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
class BeaconsChart : public QwtPlot {
    Q_OBJECT
public:
    explicit BeaconsChart(QWidget* parent = Q_NULLPTR);
public slots:
    void repaintEnvironement();
private:
    QwtPlotCurve*   _enabledBeacons{new QwtPlotCurve()};
    QwtPlotCurve*   _disabledBeacons{new QwtPlotCurve()};
    QwtSymbol*      _enabledSymbol{new QwtSymbol};
    QwtSymbol*      _disabledSymbol{new QwtSymbol};
};

#endif // BEACONSCHART_H
