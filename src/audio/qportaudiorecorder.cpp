#include "qportaudiorecorder.h"
#include <QDebug>
QPortAudioRecorder::QPortAudioRecorder(QObject *parent) : QObject(parent) {
    initialize();
}

bool QPortAudioRecorder::setCurrentDevice(PaDeviceIndex index) {
    if (index < Pa_GetDeviceCount() && isInputDevice(index)) {
        return restartDevice(index, sampleRate());
    }
    return false;
}

bool QPortAudioRecorder::setSampleRate(Real sampleRate) {
    if ((isSampleRateSupported(sampleRate) == PaErrorCode::paNoError)) {
        return restartDevice(currentDevice(), sampleRate);
    }
    return false;
}

bool QPortAudioRecorder::setFrameLength(uint frameLength) {
    _frameLength = frameLength;
    return true;
}

bool QPortAudioRecorder::record() {
    const PaError err = Pa_StartStream(_dataStream);
    if ( err != paNoError ) {
        qWarning() << "PortAudio error: %s\n" << Pa_GetErrorText(err);
        return false;
    }
    return isRunning();
}

bool QPortAudioRecorder::stop() {
    if (isRunning()) {
        PaError err = Pa_AbortStream(_dataStream);
        if ( err != paNoError ) {
            qWarning() << "PortAudio error: %s\n" << Pa_GetErrorText(err);
            return false;
        }
        err = Pa_CloseStream(_dataStream);
        if ( err != paNoError ) {
            qWarning() << "PortAudio error: %s\n" << Pa_GetErrorText(err);
            return false;
        }
        return true;
    }
    return true;
}


PaStreamCallbackResult QPortAudioRecorder::bufferReady(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags)
{
    return paContinue;
}

bool QPortAudioRecorder::initialize() {
     PaError err = Pa_Initialize();
     _isInitialized = (err == paNoError);
     if( err != paNoError ) {
         qWarning() << "PortAudio error: %s\n" << Pa_GetErrorText(err);
         return false;
     }
     return restartDevice(Pa_GetDefaultInputDevice(), defaultDeviceSampleRate(Pa_GetDefaultInputDevice()));
}

bool QPortAudioRecorder::restartDevice(PaDeviceIndex index, Real sampleRate) {
    _outputDeviceParam.channelCount = 2;
    _outputDeviceParam.device = Pa_GetDefaultOutputDevice();
    _outputDeviceParam.sampleFormat = paFloat32;
    _outputDeviceParam.suggestedLatency = latency();
    _outputDeviceParam.hostApiSpecificStreamInfo = NULL;


    _inputDeviceParam.channelCount = 1;
    _inputDeviceParam.device = index;
    _inputDeviceParam.sampleFormat = paFloat32;
    _inputDeviceParam.suggestedLatency = latency();
    _inputDeviceParam.hostApiSpecificStreamInfo = NULL;

    _sampleRate = sampleRate;

    const PaError err = Pa_OpenStream(&_dataStream, &_inputDeviceParam, NULL, _sampleRate, _frameLength, paClipOff, &QPortAudioRecorder::PortAudioCallback, this);
    if( err != paNoError ) {
         qWarning() << "PortAudio error: %s\n" << Pa_GetErrorText(err);
         return false;
    }
    return true;
}

int QPortAudioRecorder::PortAudioCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    return ((QPortAudioRecorder*)userData)->bufferReady(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags);
}
