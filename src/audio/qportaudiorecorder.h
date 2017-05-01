#ifndef QPORTAUDIO_H
#define QPORTAUDIO_H
#include "config.h"

#include <util/singleton.h>
#include <portaudio.h>
#include <QObject>
#include <QAudioFormat>
#include <QAudioBuffer>
class QPortAudioRecorder : public QObject {
    Q_OBJECT
public:
    explicit QPortAudioRecorder(QObject* parent = Q_NULLPTR);
    enum ChannelCount { Mono = 1, Stereo = 2 };
    static inline uint defaultInputDeviceCount() { return Pa_GetDefaultInputDevice(); }
    static inline uint defaultOutputDeviceCount() { return Pa_GetDefaultOutputDevice(); }
    static inline uint deviceCount(){ return Pa_GetDeviceCount(); }
    static inline QString deviceName(uint index)  { return Pa_GetDeviceInfo(index)->name; }
    static inline Real defaultDeviceSampleRate(PaDeviceIndex index) { return Pa_GetDeviceInfo(index)->defaultSampleRate; }
    static inline bool isInputDevice(PaDeviceIndex index) { return Pa_GetDeviceInfo(index)->maxInputChannels > 0; }

    inline double currentStreamTimestamp() const { return Pa_GetStreamTime(_dataStream); }
    inline bool isRunning() const { return Pa_IsStreamActive(_dataStream); }
    inline bool isInitialized() const { return _isInitialized; }
    inline int currentDevice() const { return _inputDeviceParam.device;  }
    inline uint frameLength() const { return _frameLength; }
    inline Real sampleRate() const { return _sampleRate; }
    inline Real latency() const { return _inputDeviceParam.suggestedLatency; }

    bool setCurrentDevice(PaDeviceIndex index);
    bool setSampleRate(Real sampleRate);
    bool setFrameLength(uint frameLength);

    QAudioFormat audioFormat() const;
public slots:
    bool record();
    bool stop();
signals:
    void onBufferReady(const QAudioBuffer&, PaStreamCallbackFlags) const;
    void onError(PaError, const QString&) const;
    void onRecondingStarted() const;
    void onRecondingStoped() const;
protected:
    virtual PaStreamCallbackResult  bufferReady(const void*,void *, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags) const;
private:
    PaStream*           _dataStream;
    PaStreamParameters  _inputDeviceParam;
    PaStreamParameters  _outputDeviceParam;
    Real                _sampleRate{44100.0};
    uint                _frameLength{1024};
    bool                _isInitialized{false};

    static int PortAudioCallback(const void*, void*, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*);
    bool initialize();
    bool restartDevice(PaDeviceIndex index, Real sampleRate);
    inline PaError isSampleRateSupported(Real sampleRate) const { return  Pa_IsFormatSupported(&_inputDeviceParam, &_outputDeviceParam, sampleRate); }
};
#define QPortAudioRecorderInstance Singleton<QPortAudioRecorder>::instance()

#endif // QPORTAUDIO_H
