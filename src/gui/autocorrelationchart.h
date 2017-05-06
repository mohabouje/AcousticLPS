#ifndef CORRELATIONCHART_H
#define CORRELATIONCHART_H

#include "config.h"
#include "waveformchart.h"
#include <complex>
#include <fftw3.h>
class AutoCorrelationChart : public WaveFormChart
{
    Q_OBJECT
public:
    explicit AutoCorrelationChart(QWidget *parent = 0);
public slots:
    void setData(float *data, uint size);
    void setBufferSize(double sampleRate, double secs);
private:
    float*                      _input;
    float*                      _autocor;
    uint                        _inputSize;
    uint                        _fftSize;
    fftwf_plan                  _fftPlan;
    fftwf_plan                  _ifftPlan;
    std::complex<float>*        _tmp;
    std::complex<float>*        _fft;
};

#endif // CORRELATIONCHART_H
