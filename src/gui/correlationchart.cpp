#include "correlationchart.h"
#include <QDebug>
#include <qwt_scale_widget.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
CorrelationChart::CorrelationChart(QWidget *parent) : WaveFormChart(parent)
{
    setAxisScale(QwtPlot::yLeft, -1, 1);

    QwtPlotGrid* grid = new QwtPlotGrid();
    grid->enableXMin(true);
    grid->enableYMin(true);
    grid->setMajorPen(QPen(Qt::black, 0, Qt::DotLine));
    grid->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
    grid->attach(this);

    _waveForm->setPen(* new QPen(Qt::red, 2, Qt::SolidLine));

    QFrame* frame = qobject_cast<QFrame*>(canvas());
    frame->setFrameStyle(QFrame::StyledPanel);
    plotLayout()->setAlignCanvasToScales( true );
}

void CorrelationChart::setData(const float *data, uint size) {
    Vector vec(size);
    for (Size i=0; i<size; i++) {
        vec(i) = data[i];
    }

    vec = _gcc.compute(vec, vec);
    const Real _max = vec.max();
    const Size down = std::round(size / _yData.size());
    const uint N = _yData.size();
    for (Size n=0; n<N; n++) {
        _yData[n] = vec(n*down) / _max;
    }

    if (isVisible()) {
        replot();
    }
}

