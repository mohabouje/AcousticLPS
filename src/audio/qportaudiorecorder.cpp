#include "qportaudiorecorder.h"
#include <QDebug>
QPortAudioRecorder::QPortAudioRecorder(QObject *parent) : QPortAudioDevice(parent) {
    initialize();
}

bool QPortAudioRecorder::setCurrentDevice(PaDeviceIndex index) {
    if (index < Pa_GetDeviceCount() && isInputDevice(index)) {
        return restartDevice(index, sampleRate(), frameLength());
    }
    return false;
}

bool QPortAudioRecorder::record() {
    if (isRunning()) {
        return true;
    }

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
        PaError err = Pa_StopStream(_dataStream);
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
    }

    const double sr = defaultDeviceSampleRate(Pa_GetDefaultInputDevice());
    const unsigned int fl = 0.1 * sr;
    return _isInitialized  && restartDevice(Pa_GetDefaultInputDevice(), sr, fl);
}


bool QPortAudioRecorder::restartDevice(PaDeviceIndex index, double sampleRate, unsigned long frameLength) {
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
    _frameLength = frameLength;
    const PaError err = Pa_OpenStream(&_dataStream, &_inputDeviceParam, NULL, _sampleRate, _frameLength, paClipOff, &QPortAudioRecorder::PortAudioCallback, this);
    if( err != paNoError ) {
         emit onError(err, Pa_GetErrorText(err));
         return false;
    }
    return true;
}


