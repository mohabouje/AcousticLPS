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

QAudioFormat QPortAudioRecorder::audioFormat() const {
    QAudioFormat format;
    format.setByteOrder(QAudioFormat::BigEndian);
    format.setSampleRate(_sampleRate);
    format.setSampleType(QAudioFormat::Float);
    format.setSampleSize(sizeof(float) * 8);
    format.setChannelCount(Mono);
    format.setCodec("audio/pcm");
    return format;
}

bool QPortAudioRecorder::record() {
    const PaError err = Pa_StartStream(_dataStream);
    if ( err != paNoError ) {
        emit onError(err, Pa_GetErrorText(err));
        return false;
    }
    const bool recording = isRunning();
    if (recording) {
        emit onRecondingStarted();
    }
    return recording;
}

bool QPortAudioRecorder::stop() {
    if (isRunning()) {
        PaError err = Pa_AbortStream(_dataStream);
        if ( err != paNoError ) {
            emit onError(err, Pa_GetErrorText(err));
            return false;
        }
        err = Pa_CloseStream(_dataStream);
        if ( err != paNoError ) {
            emit onError(err, Pa_GetErrorText(err));
            return false;
        }
        const bool stoped = !isRunning();
        if (stoped) {
            emit onRecondingStoped();
        }
        return stoped;
    }
    return true;
}


PaStreamCallbackResult QPortAudioRecorder::bufferReady(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags) {
    Q_UNUSED(outputBuffer);
    Q_UNUSED(timeInfo);
    Q_UNUSED(statusFlags);
    emit onBufferReady((float*)(inputBuffer), framesPerBuffer);
    return paContinue;
}

bool QPortAudioRecorder::initialize() {
     PaError err = Pa_Initialize();
     _isInitialized = (err == paNoError);
     if( err != paNoError ) {
         emit onError(err, Pa_GetErrorText(err));
         return false;
     }
     return restartDevice(Pa_GetDefaultInputDevice(), defaultDeviceSampleRate(Pa_GetDefaultInputDevice()));
}

bool QPortAudioRecorder::restartDevice(PaDeviceIndex index, Real sampleRate) {
    _outputDeviceParam.channelCount = Stereo;
    _outputDeviceParam.device = Pa_GetDefaultOutputDevice();
    _outputDeviceParam.sampleFormat = paFloat32;
    _outputDeviceParam.suggestedLatency = Pa_GetDeviceInfo(_outputDeviceParam.device)->defaultLowInputLatency;
    _outputDeviceParam.hostApiSpecificStreamInfo = NULL;


    _inputDeviceParam.channelCount = Mono;
    _inputDeviceParam.device = index;
    _inputDeviceParam.sampleFormat = paFloat32;
    _inputDeviceParam.suggestedLatency = Pa_GetDeviceInfo(index)->defaultLowInputLatency;
    _inputDeviceParam.hostApiSpecificStreamInfo = NULL;

    _sampleRate = sampleRate;
    _frameLength = 0.2 * sampleRate;
    const PaError err = Pa_OpenStream(&_dataStream, &_inputDeviceParam, NULL, _sampleRate, _frameLength, paClipOff, &QPortAudioRecorder::PortAudioCallback, this);
    if( err != paNoError ) {
         emit onError(err, Pa_GetErrorText(err));
         return false;
    }
    return true;
}

int QPortAudioRecorder::PortAudioCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    return ((QPortAudioRecorder*)userData)->bufferReady(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags);
}
