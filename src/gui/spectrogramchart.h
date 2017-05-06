#ifndef SPECTROGRAMCHART_H
#define SPECTROGRAMCHART_H

#include "waveformchart.h"
class SpectrogramChart  : public WaveFormChart {
public:
    explicit SpectrogramChart(QWidget* parent = Q_NULLPTR);
public slots:
    void setData(const float *data, uint size);
};

#endif // SPECTROGRAMCHART_H
