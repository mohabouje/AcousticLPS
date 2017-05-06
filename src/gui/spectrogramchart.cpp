#include "spectrogramchart.h"
#include "config.h"
#include <dsp/dsp.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
SpectrogramChart::SpectrogramChart(QWidget* parent) : WaveFormChart(parent)
{

    setAxisScale(QwtPlot::yLeft, -100, 100);

    QwtPlotGrid* grid = new QwtPlotGrid();
    grid->enableXMin(true);
    grid->enableYMin(true);
    grid->setMajorPen(QPen(Qt::black, 0, Qt::DotLine));
    grid->setMinorPen(QPen(Qt::gray, 0 , Qt::DotLine));
    grid->attach(this);

    _waveForm->setPen(QPen(Qt::red, 2, Qt::SolidLine));

    QFrame* frame = qobject_cast<QFrame*>(canvas());
    frame->setFrameStyle(QFrame::StyledPanel);
    plotLayout()->setAlignCanvasToScales( true );
}

SpectrogramChart::~SpectrogramChart() {
   delete[] _input;
   delete[] _fft;
   fftwf_destroy_plan(_fftPlan);
}

void SpectrogramChart::setData(float *data, uint size) {
    std::memcpy(_input, data, size);

    fftwf_execute(_fftPlan);

    for (uint i=0; i<_data.size; i++) {
        _data.y[i] = 20.0 * std::log10(std::abs(_fft[i]));
    }

    replot();
}

void SpectrogramChart::setBufferSize(double sampleRate, double secs) {
    _inputSize = static_cast<uint>(sampleRate * secs);
    _fftSize = static_cast<Size>(DSP::Math::nextPow2(_inputSize));

    _fft = new std::complex<float>[_fftSize]{std::complex<float>(0.,0.)};
    _input = new float[_fftSize]{0};

    _data.size = _fftSize / 2 + 1;
    _data.x = new double[_data.size]{0};
    _data.y = new double[_data.size]{0};

    _waveForm->setRawSamples(_data.x, _data.y, _data.size);
    _fftPlan = fftwf_plan_dft_r2c_1d(_fftSize, _input, reinterpret_cast<fftwf_complex*>(_fft), FFTW_ESTIMATE);

    setAxisScale(QwtPlot::xBottom, 0.0, M_PI);
    const arma::vec xValues = arma::linspace(0, M_PI, _data.size);
    std::copy(xValues.begin(), xValues.end(), _data.x);
}
