#include "routeschart.h"
RoutesChart::RoutesChart(QWidget* parent) : BeaconsChart(parent) {
    _grid->enableXMin(true);
    _grid->enableYMin(true);
    _grid->setMajorPen(QPen(Qt::black, 0, Qt::DotLine));
    _grid->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
    _grid->attach(this);
}

void RoutesChart::repaintEnvironement() {
    if (_showBeacons) {
        BeaconsChart::repaintEnvironement();
    } else {
        BeaconsChart::clear();
    }
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
