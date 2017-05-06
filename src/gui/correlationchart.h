#ifndef CORRELATIONCHART_H
#define CORRELATIONCHART_H

#include <dsp/generalizedcrosscorrelation.h>

#include "waveformchart.h"
class CorrelationChart : public WaveFormChart
{
    Q_OBJECT
public:
    explicit CorrelationChart(QWidget *parent = 0);
public slots:
    void setData(const float *data, uint size);
private:
    DSP::GeneralizedCrossCorrelation    _gcc;
};

#endif // CORRELATIONCHART_H
