#ifndef WAVEFORMCHART_H
#define WAVEFORMCHART_H
#include <config.h>
#include <QAudioBuffer>
#include <QWidget>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <boost/circular_buffer.hpp>
class WaveFormChart : public QwtPlot
{
    Q_OBJECT
public:
    explicit WaveFormChart(QWidget *parent = 0);
    void setBufferSize(Real sampleRate, Real secs);
    void insert(const float* data, uint size);

private:
    QwtPlotCurve*                 _waveForm{new QwtPlotCurve()};
    QVector<double>               _xData;
    QVector<double>               _yData;
    static constexpr uint        DownSampleFactor{10};
};

#endif // WAVEFORMCHART_H
