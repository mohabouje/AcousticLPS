#ifndef QPORTAUDIO_H
#define QPORTAUDIO_H

#include <util/singleton.h>
#include "qportaudiodevice.h"
class QPortAudioRecorder : public QPortAudioDevice {
    Q_OBJECT
public:
    explicit QPortAudioRecorder(QObject* parent = Q_NULLPTR);
    bool initialize();
signals:
    void onRecondingStarted() const;
    void onRecondingStoped() const;
public slots:
    bool setCurrentDevice(PaDeviceIndex index);
    bool record();
    bool stop();
private:
    virtual PaStreamCallbackResult  bufferReady(const void*,void *, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags) ;
    bool restartDevice(PaDeviceIndex index, double sampleRate, unsigned long frameLength);
};
#define QPortAudioRecorderInstance Singleton<QPortAudioRecorder>::instance()

#endif // QPORTAUDIO_H
