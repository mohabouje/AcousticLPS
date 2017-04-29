#ifndef BEACONSCHART_H
#define BEACONSCHART_H

#include <model/qbeacon.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>
class BeaconsChart : public QwtPlot {
    Q_OBJECT
public:
    explicit BeaconsChart(QWidget* parent = Q_NULLPTR);
public slots:
    void beaconSelected(const QBeacon& beacon);
    void repaintEnvironement();
private:
    QwtPlotCurve*   _enabledBeacons{new QwtPlotCurve()};
    QwtPlotCurve*   _disabledBeacons{new QwtPlotCurve()};
    QwtPlotCurve*   _selectedBeacons{new QwtPlotCurve()};
    QBeacon         _beacon;
};


class BeaconPicker : public QwtPlotPicker {
    Q_OBJECT
public:
    BeaconPicker(int xAxis, int yAxis, RubberBand rubberBand, DisplayMode trackerMode, QWidget* canvas);
protected:
    QwtText trackerTextF(const QPointF& pos) const override;
};







#endif // BEACONSCHART_H
