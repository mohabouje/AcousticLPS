#include "autocorrelationchart.h"
#include <dsp/dsp.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
AutoCorrelationChart::AutoCorrelationChart(QWidget *parent) : WaveFormChart(parent)
{
    setAxisScale(QwtPlot::yLeft, -1, 1);

    QwtPlotGrid* grid = new QwtPlotGrid();
    grid->enableXMin(true);
    grid->enableYMin(true);
    grid->setMajorPen(QPen(Qt::black, 0, Qt::DotLine));
    grid->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
    grid->attach(this);

    _waveForm->setPen(QPen(Qt::red, 2, Qt::SolidLine));
}


void AutoCorrelationChart::setData(float *data, uint size) {
    _autocor.compute(data, size);
    std::copy(_autocor.output(), _autocor.output() + _autocor.outputSize(), _data.y);
    replot();
}

void AutoCorrelationChart::setBufferSize(double sampleRate, double secs) {
    _autocor.setBufferSize(sampleRate, secs);

    _data.size = _autocor.outputSize();
    _data.x = new double[_data.size]{0};
    _data.y = new double[_data.size]{0};

    _waveForm->setRawSamples(_data.x, _data.y, _data.size);
    setAxisScale(QwtPlot::xBottom, 0.0, M_PI);
    const arma::vec xValues = arma::linspace(0, M_PI, _data.size);
    std::copy(xValues.begin(), xValues.end(), _data.x);
}

