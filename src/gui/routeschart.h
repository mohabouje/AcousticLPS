#ifndef ROUTESCHART_H
#define ROUTESCHART_H
#include <config.h>
#include <math/trilateration.h>
#include "beaconschart.h"
#include <qwt_plot_grid.h>
class RoutesChart : public BeaconsChart {
    Q_OBJECT
public:
    explicit RoutesChart(QWidget* parent = Q_NULLPTR);
public slots:
    void estimateRoute(const QVector<QMeasure>& measures);
    void showGrid(bool);
    void showTrilateration(bool);
private:
    QwtPlotGrid*                    _grid{new QwtPlotGrid};
    QwtPlotCurve*                   _trilaterationCurve{new QwtPlotCurve};
    Trilateration*                  _trilateration{new Trilateration};
};

#endif // ROUTESCHART_H
