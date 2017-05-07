#ifndef SPECTROGRAMCHART_H
#define SPECTROGRAMCHART_H
#include "waveformchart.h"
#include <dsp/powerspectraldensity.h>
class PowerSpectralDensityChart  : public WaveFormChart {
public:
    explicit PowerSpectralDensityChart(QWidget* parent = Q_NULLPTR);
public slots:
    void setData(float *data, uint size);
    void setBufferSize(double sampleRate, double secs);
private:
    PowerSpectralDensity    _psd;
};


#endif // SPECTROGRAMCHART_H
