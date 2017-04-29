#ifndef ROUTESCHART_H
#define ROUTESCHART_H

#include <math/trilateration.h>
#include "beaconschart.h"
#include <qwt_plot_grid.h>
class RoutesChart : public BeaconsChart {
    Q_OBJECT
public:
    explicit RoutesChart(QWidget* parent = Q_NULLPTR);
public slots:
    void plotRoute(const QVector<QMeasure>& measures);
    void repaintEnvironement() override;
    void updateEnvironement() override;
    void showBeacons(bool);
    void showGrid(bool);
    void showTrilateration(bool);
private slots:
    void flushTrilaterationCurves();
    void traceHyperbolic(const QMeasure& measure);
private:
    bool                            _showBeacons{true};
    bool                            _showTrilateration{true};
    QwtPlotGrid*                    _grid{new QwtPlotGrid};
    QHash<QBeacon, QwtPlotCurve*>   _trilaterationCurves;
    Trilateration*                  _trilateration{new Trilateration};
};

#endif // ROUTESCHART_H
