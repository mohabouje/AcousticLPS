#include "waveformchart.h"
#include <QDebug>
WaveFormChart::WaveFormChart(QWidget *parent) : QwtPlot(parent)
{
    _waveForm->setStyle(QwtPlotCurve::Lines);
    _waveForm->attach(this);

    setAxisScale(QwtPlot::yLeft, -1.0, 1.0);
    enableAxis(QwtPlot::xBottom, false);
    enableAxis(QwtPlot::yLeft, false);
}

void WaveFormChart::setBufferSize(Real sampleRate, Real secs) {
    const uint size = std::floor(sampleRate * secs);
    _xData = QVector<double>(size, 0);
    _yData = QVector<double>(size, 0);

    const Vector xValues = arma::linspace(0, secs, size);
    for (uint i=0; i<size; i++) {
        _xData[i] = xValues[i];
    }

    _waveForm->setRawSamples(_xData.data(), _yData.data(), size);
    setAxisScale(QwtPlot::xBottom, 0.0, secs);

}

void WaveFormChart::insert(const float* data, uint size) {
    std::copy(_yData.begin() + size, _yData.end(), _yData.begin());
    const uint end = _yData.size();
    const uint start = end - size;
    for (uint i=start; i<end; i++) {
        _yData[i] = static_cast<double>(data[i-start]);
    }
    this->replot();
}
