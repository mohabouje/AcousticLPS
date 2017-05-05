#ifndef QPORTAUDIODEVICE_H
#define QPORTAUDIODEVICE_H

#include <portaudio.h>
#include <QObject>
class QPortAudioDevice : public QObject {
    Q_OBJECT
public:
    static inline bool isInputDevice(PaDeviceIndex index) { return Pa_GetDeviceInfo(index)->maxInputChannels > 0; }
    static inline bool isOutputDevice(PaDeviceIndex index) { return Pa_GetDeviceInfo(index)->maxOutputChannels > 0; }
    static inline double defaultDeviceSampleRate(PaDeviceIndex index) { return Pa_GetDeviceInfo(index)->defaultSampleRate; }
    static inline QString deviceName(unsigned long index)  { return Pa_GetDeviceInfo(index)->name; }
    enum ChannelCount { Mono = 1, Stereo = 2 };

    explicit QPortAudioDevice(QObject* parent = Q_NULLPTR);
    virtual bool initialize() = 0;

    inline double currentStreamTimestamp() const { return Pa_GetStreamTime(_dataStream); }
    inline bool isRunning() const { return Pa_IsStreamActive(_dataStream); }
    inline bool isInitialized() const { return _isInitialized; }
    inline int currentDevice() const { return _inputDeviceParam.device;  }
    inline unsigned long frameLength() const { return _frameLength; }
    inline double sampleRate() const { return _sampleRate; }
    inline double latency() const { return _inputDeviceParam.suggestedLatency; }
public slots:
    virtual bool setCurrentDevice(PaDeviceIndex index) = 0;
    bool setSampleRate(double sampleRate);
    bool setFrameLength(unsigned long frameLength);
signals:
    void onBufferReady(float*, unsigned long size) const;
    void onError(int, const QString&) const;
protected:
    virtual bool restartDevice(PaDeviceIndex index, double sampleRate, unsigned long frameLength) = 0;
    virtual PaStreamCallbackResult  bufferReady(const void*,void *, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags) = 0;
    inline PaError isSampleRateSupported(double sampleRate) const { return  Pa_IsFormatSupported(&_inputDeviceParam, &_outputDeviceParam, sampleRate); }
    static int PortAudioCallback(const void*, void*, unsigned long, const PaStreamCallbackTimeInfo*, PaStreamCallbackFlags, void*);
    PaStream*               _dataStream;
    PaStreamParameters      _inputDeviceParam;
    PaStreamParameters      _outputDeviceParam;
    double                  _sampleRate{44100.0};
    unsigned long            _frameLength{1024};
    bool                    _isInitialized{false};
};
#endif // QPORTAUDIODEVICE_H
