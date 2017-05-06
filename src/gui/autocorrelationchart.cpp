#include "autocorrelationchart.h"
#include <dsp/dsp.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
#include <QDebug>
AutoCorrelationChart::AutoCorrelationChart(QWidget *parent) : WaveFormChart(parent)
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

void AutoCorrelationChart::setData(float *data, uint size) {
    std::memcpy(_input, data, size);

    fftwf_execute(_fftPlan);
    for (uint i = 0;  i< _fftSize; i++) {
       _tmp[i] = _fft[i] * std::conj(_fft[i]);
    }
    fftwf_execute(_ifftPlan);

    float _max = *std::max_element(_autocor, _autocor + _data.size);
    for (uint i=0; i<_data.size; i++) {
        _data.y[i] = _autocor[i] / _max;
    }

    replot();
}

void AutoCorrelationChart::setBufferSize(double sampleRate, double secs) {
    _inputSize = static_cast<uint>(sampleRate * secs);
    _fftSize = static_cast<uint>(2 * _inputSize - 1);

    _fft = new std::complex<float>[_fftSize];
    _tmp = new std::complex<float>[_fftSize];
    _input = new float[_fftSize]{0};
    _autocor = new float[_fftSize]{0};

    _data.size = _inputSize / 4;
    _data.x = new double[_data.size]{0};
    _data.y = new double[_data.size]{0};

    _waveForm->setRawSamples(_data.x, _data.y, _data.size);
    _fftPlan = fftwf_plan_dft_r2c_1d(_fftSize, _input, reinterpret_cast<fftwf_complex*>(_fft), FFTW_ESTIMATE);
    _ifftPlan = fftwf_plan_dft_c2r_1d(_fftSize, reinterpret_cast<fftwf_complex*>(_tmp), _autocor, FFTW_ESTIMATE);
    setAxisScale(QwtPlot::xBottom, 0.0, M_PI);
    const arma::vec xValues = arma::linspace(0, M_PI, _data.size);
    std::copy(xValues.begin(), xValues.end(), _data.x);
}

