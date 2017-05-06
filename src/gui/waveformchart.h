#ifndef WAVEFORMCHART_H
#define WAVEFORMCHART_H
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
class WaveFormChart : public QwtPlot
{
    Q_OBJECT
public:
    explicit WaveFormChart(QWidget *parent = 0);
    virtual void setBufferSize(double sampleRate, double secs);
    virtual void setData(const float* data, uint size);
protected:
    QwtPlotCurve*                 _waveForm{new QwtPlotCurve()};
    QVector<double>               _xData;
    QVector<double>               _yData;
    static constexpr uint        DownSampleFactor{20};
};

#endif // WAVEFORMCHART_H
