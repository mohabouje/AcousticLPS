#ifndef ROUTESCHART_H
#define ROUTESCHART_H
#include "beaconschart.h"

#include <math/trilateration.h>

#include <qwt_plot_grid.h>
class TrilaterationChart : public BeaconsChart {
    Q_OBJECT
public:
    explicit TrilaterationChart(QWidget* parent = Q_NULLPTR);
public slots:
    virtual void setMeasures(const QVector<QMeasure>& measures);
    virtual void repaintTrilateration();
    void showGrid(bool);
    void showTrilateration(bool);
private:
    QVector<QMeasure>               _measures;
    QwtPlotGrid*                    _grid{new QwtPlotGrid};
    QwtPlotCurve*                   _trilaterationCurve{new QwtPlotCurve};
};

#endif // ROUTESCHART_H
