#ifndef SPECTROGRAMCHART_H
#define SPECTROGRAMCHART_H
#include "config.h"
#include "waveformchart.h"
#include <complex>
#include <fftw3.h>
class SpectrogramChart  : public WaveFormChart {
public:
    explicit SpectrogramChart(QWidget* parent = Q_NULLPTR);
    ~SpectrogramChart();
public slots:
    void setData(float *data, uint size);
    void setBufferSize(double sampleRate, double secs);
private:
    float*                      _input;
    uint                        _inputSize;
    uint                        _fftSize;
    fftwf_plan                  _fftPlan;
    std::complex<float>*        _fft;
};


#endif // SPECTROGRAMCHART_H
