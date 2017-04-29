#include "helper.h"

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_point_data.h>

void Gui::plot(const Vector &y) {
    const Size N = y.size();
    Vector x(N);
    for(Size i=0; i<N; i++) {
        x(i) = i;
    }

    QwtPlot *myPlot = new QwtPlot(NULL);
    myPlot->setFixedWidth(300);
    QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1");
    curve1->setSamples(x.memptr(), y.memptr(), N);
    curve1->attach(myPlot);

    myPlot->replot();
    myPlot->show();
}
