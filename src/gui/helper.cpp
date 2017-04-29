#include "helper.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_point_data.h>

void Gui::plot(const Vector &y) {
    const Size N = y.size();
    QwtData data(N);
    data.yData = y;
    data.xData = arma::linspace(0, N, N);
    plot(data);
}

void Gui::plot(QwtData data) {
    QwtPlot *myPlot = new QwtPlot(NULL);
    QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1");
    curve1->setSamples(data.x(), data.y(), data.size());
    curve1->attach(myPlot);

    const std::pair<const Real*, const Real*> xLimit = std::minmax_element(data.x(), data.x() + data.size());
    const std::pair<const Real*, const Real*> yLimit = std::minmax_element(data.y(), data.y() + data.size());
    myPlot->setAxisScale(QwtPlot::xBottom, *xLimit.first, *xLimit.second);
    myPlot->setAxisScale(QwtPlot::yRight, *yLimit.first, *yLimit.second);
    myPlot->replot();
    myPlot->show();
}
