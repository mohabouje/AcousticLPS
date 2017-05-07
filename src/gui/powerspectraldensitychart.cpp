#include "powerspectraldensitychart.h"
#include <qwt_plot_curve.h>
PowerSpectralDensityChart::PowerSpectralDensityChart(QWidget* parent) : WaveFormChart(parent) {

    setAxisScale(QwtPlot::yLeft, -100, 100);
    _waveForm->setPen(QPen(Qt::red, 2, Qt::SolidLine));
}

void PowerSpectralDensityChart::setData(float *data, uint size) {
    _psd.compute(data, size);
    std::copy(_psd.output(), _psd.output() + _psd.outputSize(), _data.y);
    replot();
}

void PowerSpectralDensityChart::setBufferSize(double sampleRate, double secs) {
    _psd.setBufferSize(sampleRate, secs);

    _data.size = _psd.outputSize();
    _data.x = new double[_data.size]{0};
    _data.y = new double[_data.size]{0};

    _waveForm->setRawSamples(_data.x, _data.y, _data.size);
    setAxisScale(QwtPlot::xBottom, 0.0, M_PI);
    const arma::vec xValues = arma::linspace(0, M_PI, _data.size);
    std::copy(xValues.begin(), xValues.end(), _data.x);
}
