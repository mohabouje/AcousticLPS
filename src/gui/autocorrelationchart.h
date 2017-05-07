#ifndef CORRELATIONCHART_H
#define CORRELATIONCHART_H

#include "config.h"
#include "waveformchart.h"
#include <dsp/autocorrelation.h>
class AutoCorrelationChart : public WaveFormChart
{
    Q_OBJECT
public:
    explicit AutoCorrelationChart(QWidget *parent = 0);
public slots:
    void setData(float *data, uint size);
    void setBufferSize(double sampleRate, double secs);
private:
    Autocorrelation     _autocor;
};

#endif // CORRELATIONCHART_H
