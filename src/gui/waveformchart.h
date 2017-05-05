#ifndef WAVEFORMCHART_H
#define WAVEFORMCHART_H
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
class WaveFormChart : public QwtPlot
{
    Q_OBJECT
public:
    explicit WaveFormChart(QWidget *parent = 0);
    void setBufferSize(double sampleRate, double secs);
    void insert(const float* data, uint size);

private:
    QwtPlotCurve*                 _waveForm{new QwtPlotCurve()};
    QVector<double>               _xData;
    QVector<double>               _yData;
    static constexpr uint        DownSampleFactor{10};
};

#endif // WAVEFORMCHART_H
