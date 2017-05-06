#include "spectrogramchart.h"
#include "config.h"
#include <dsp/dsp.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
SpectrogramChart::SpectrogramChart(QWidget* parent) : WaveFormChart(parent)
{

    setAxisScale(QwtPlot::yLeft, 0, 100);

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

void SpectrogramChart::setData(const float *data, uint size) {
    Vector vec(size);
    for (Size i=0; i<size; i++) {
        vec(i) = data[i];
    }

    const Size fftSize = static_cast<Size>(DSP::Math::nextPow2(2*size-1));
    const Complex fft = arma::fft(vec, fftSize);
    const Size down = std::round(fftSize / _yData.size());
    const uint N = _yData.size();
    for (Size n=0; n<N; n++) {
        const Real value = std::abs(fft(n*down));
        _yData[n] = value * value;
    }

    if (isVisible()) {
        replot();
    }
}
