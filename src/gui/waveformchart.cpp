#include "waveformchart.h"
#include "config.h"
WaveFormChart::WaveFormChart(QWidget *parent) : QwtPlot(parent)
{
    _waveForm->setStyle(QwtPlotCurve::Lines);
    _waveForm->attach(this);

    setAxisScale(QwtPlot::yLeft, -1.0, 1.0);
    enableAxis(QwtPlot::xBottom, false);
    enableAxis(QwtPlot::yLeft, false);
}

void WaveFormChart::setBufferSize(double sampleRate, double secs) {
    setAxisScale(QwtPlot::xBottom, 0.0, secs);
    const uint size = std::floor(sampleRate * secs / DownSampleFactor);
    _xData = QVector<double>(size, 0);
    _yData = QVector<double>(size, 0);

    const arma::vec xValues = arma::linspace(0, secs, size);
    std::copy(xValues.begin(), xValues.end(), _xData.begin());
    _waveForm->setRawSamples(_xData.data(), _yData.data(), size);
}


void WaveFormChart::setData(const float* data, uint size) {
    const uint N = std::floor(1.0 * size / DownSampleFactor);
    QVector<double> tmp(N);
    for (Size n=0; n<N; n++) {
        tmp[n] = data[n*DownSampleFactor];
    }

    std::copy(_yData.begin() + N, _yData.end(), _yData.begin());
    std::copy(tmp.begin(), tmp.end(), _yData.end() - N);
    replot();
}
