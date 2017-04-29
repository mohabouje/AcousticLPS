#ifndef ROUTESCHART_H
#define ROUTESCHART_H

#include "beaconschart.h"
#include <qwt_plot_grid.h>
class RoutesChart : public BeaconsChart {
    Q_OBJECT
public:
    explicit RoutesChart(QWidget* parent = Q_NULLPTR);

public slots:
    void repaintEnvironement() override;
    void showBeacons(bool showBeacons);
    void showGrid(bool show);
private:
    bool            _showBeacons{true};
    QwtPlotGrid*    _grid{new QwtPlotGrid};
};

#endif // ROUTESCHART_H
