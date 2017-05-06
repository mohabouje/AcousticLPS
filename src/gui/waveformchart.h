#ifndef WAVEFORMCHART_H
#define WAVEFORMCHART_H
#include "config.h"
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
class WaveFormChart : public QwtPlot
{
    Q_OBJECT
public:
    explicit WaveFormChart(QWidget *parent = 0);
    virtual void setBufferSize(double sampleRate, double secs);
    virtual void setData(float* data, uint size);
protected:
    QwtPlotCurve*               _waveForm{new QwtPlotCurve()};
    Plot                        _data;
    static constexpr uint       DownSampleFactor{20};
};

#endif // WAVEFORMCHART_H
