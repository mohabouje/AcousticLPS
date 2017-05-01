#ifndef QPORTAUDIO_H
#define QPORTAUDIO_H
#include "config.h"
#include <portaudio.h>
#include <QObject>
class QPortAudioRecorder : public QObject
{
public:
    explicit QPortAudioRecorder(QObject* parent = Q_NULLPTR);
    static inline uint defaultInputDeviceCount() { return Pa_GetDefaultInputDevice(); }
    static inline uint defaultOutputDeviceCount() { return Pa_GetDefaultOutputDevice(); }
    static inline uint deviceCount(){ return Pa_GetDeviceCount(); }
    static inline QString deviceName(uint index)  { return Pa_GetDeviceInfo(index)->name; }


    inline uint currentHostApi() const { return _currentHostApi; }
    inline uint currentDevice() const { return _currentDevice;  }
    inline uint frameLength() const { return _frameLength; }
    inline Real sampleRate() const { return _sampleRate; }
    inline Real latency() const { return _latency; }
protected:
    virtual PaStreamCallbackResult  bufferReady(const void*,void *, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags);
private:
    PaTime          _latency;
    PaHostApiIndex  _currentHostApi;
    PaDeviceIndex   _currentDevice;
    Real            _sampleRate;
    uint            _frameLength;
    bool            _isRunning;

    static PaStreamCallbackResult PortAudioCallback(const void *inputBuffer,
                                void *outputBuffer,
                                unsigned long framesPerBuffer,
                                const PaStreamCallbackTimeInfo* timeInfo,
                                PaStreamCallbackFlags statusFlags,
                                void *userData)
    {
      return ((QPortAudioRecorder*)userData)->bufferReady(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags);
    }
};

#endif // QPORTAUDIO_H
