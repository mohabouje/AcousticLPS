#include "waveformchart.h"
#include "config.h"
WaveFormChart::WaveFormChart(QWidget *parent) : QwtPlot(parent)
{
    _waveForm->setStyle(QwtPlotCurve::Lines);
    _waveForm->attach(this);

    setAxisScale(QwtPlot::yLeft, -1.0, 1.0);
    enableAxis(QwtPlot::xBottom, false);
    enableAxis(QwtPlot::yLeft, false);

    QFrame* frame = qobject_cast<QFrame*>(canvas());
    frame->setFrameStyle(QFrame::StyledPanel);
}

void WaveFormChart::setBufferSize(double sampleRate, double secs) {
    setAxisScale(QwtPlot::xBottom, 0.0, secs);
    _data.size = std::floor(sampleRate * secs / DownSampleFactor);
    _data.x = new double[_data.size]{0};
    _data.y = new double[_data.size]{0};

    const arma::vec xValues = arma::linspace(0, secs, _data.size);
    std::copy(xValues.begin(), xValues.end(), _data.x);
    _waveForm->setRawSamples(_data.x, _data.y, _data.size);
}


void WaveFormChart::setData(float* data, uint size) {
    const uint N = std::floor(1.0 * size / DownSampleFactor);
    double* tmp = new double[N];
    for (uint n=0; n<N; n++) {
        tmp[n] = data[n*DownSampleFactor];
    }

    std::copy(_data.y + N, _data.y + _data.size, _data.y);
    std::copy(tmp, tmp + N, _data.y + _data.size - N);
    delete (tmp);
    replot();
}
