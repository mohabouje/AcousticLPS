#ifndef QPORTAUDIOPLAYER_H
#define QPORTAUDIOPLAYER_H

#include <util/singleton.h>
#include "qportaudiodevice.h"
class QPortAudioPlayer : public QPortAudioDevice {
    Q_OBJECT
public:
    explicit QPortAudioPlayer(QObject* parent = Q_NULLPTR);
    bool initialize();
signals:
    void onPlayerStarted() const;
    void onPlayerStopped() const;
public slots:
    bool setCurrentDevice(PaDeviceIndex index);
    bool play(float* buffer, unsigned int size);
    bool stop();
private:
    virtual PaStreamCallbackResult  bufferReady(const void*,void *, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags) ;
    bool restartDevice(PaDeviceIndex index, double sampleRate, unsigned long frameLength);
};
#define Player Singleton<QPortAudioPlayer>::instance()
#endif // QPORTAUDIOPLAYER_H
