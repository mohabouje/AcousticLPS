#include "waveformchart.h"

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
    _data = QwtData(size);
    _data.xData = arma::linspace(0, secs, size);
    _waveForm->setRawSamples(_data.x(), _data.y(), _data.size());
    setAxisScale(QwtPlot::xBottom, 0.0, secs);

}

void WaveFormChart::insert(const Real* data, uint size) {
    //std::copy(_data.xData.begin() + size, _data.xData.end(), _data.xData.begin());
    //std::copy(_data.xData.end() - size, _data.xData.end(), data);
    this->replot();
}
