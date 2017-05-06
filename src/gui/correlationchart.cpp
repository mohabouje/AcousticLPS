#include "correlationchart.h"
#include <QDebug>
CorrelationChart::CorrelationChart(QWidget *parent) : WaveFormChart(parent)
{
    setAxisScale(QwtPlot::yLeft, -1, 1);
    enableAxis(QwtPlot::xBottom, true);
    enableAxis(QwtPlot::yLeft, true);
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

    this->replot();
}

