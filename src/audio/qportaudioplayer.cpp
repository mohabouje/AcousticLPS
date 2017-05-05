#include "qportaudioplayer.h"
QPortAudioPlayer::QPortAudioPlayer(QObject *parent) : QPortAudioDevice(parent) {
    initialize();
}

bool QPortAudioPlayer::setCurrentDevice(PaDeviceIndex index) {
    if (index < Pa_GetDeviceCount() && isInputDevice(index)) {
        return restartDevice(index, sampleRate(), frameLength());
    }
    return false;
}

bool QPortAudioPlayer::start() {
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
        emit onPlayerStarted();
    }
    return recording;
}

bool QPortAudioPlayer::stop() {
    if (isRunning()) {
        PaError err = Pa_StopStream(_dataStream);
        if ( err != paNoError ) {
            emit onError(err, Pa_GetErrorText(err));
            return false;
        }
        const bool stoped = !isRunning();
        if (stoped) {
            emit onPlayerStopped();
        }
        return stoped;
    }
    return true;
}


PaStreamCallbackResult QPortAudioPlayer::bufferReady(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags) {
    Q_UNUSED(inputBuffer);
    Q_UNUSED(timeInfo);
    Q_UNUSED(statusFlags);
    emit onBufferReady((float*)(outputBuffer), framesPerBuffer);
    return paContinue;
}

bool QPortAudioPlayer::initialize() {
    PaError err = Pa_Initialize();
    _isInitialized = (err == paNoError);
    if( err != paNoError ) {
        emit onError(err, Pa_GetErrorText(err));
    }

    const double sr = defaultDeviceSampleRate(Pa_GetDefaultOutputDevice());
    const unsigned int fl = 0.1 * sr;
    return _isInitialized  && restartDevice(Pa_GetDefaultInputDevice(), sr, fl);
}


bool QPortAudioPlayer::restartDevice(PaDeviceIndex index, double sampleRate, unsigned long frameLength) {
    _outputDeviceParam.channelCount = Stereo;
    _outputDeviceParam.device = index;
    _outputDeviceParam.sampleFormat = paFloat32;
    _outputDeviceParam.suggestedLatency = Pa_GetDeviceInfo(_outputDeviceParam.device)->defaultLowInputLatency;
    _outputDeviceParam.hostApiSpecificStreamInfo = NULL;


    _inputDeviceParam.channelCount = Mono;
    _inputDeviceParam.device = Pa_GetDefaultInputDevice();
    _inputDeviceParam.sampleFormat = paFloat32;
    _inputDeviceParam.suggestedLatency = Pa_GetDeviceInfo(_inputDeviceParam.device)->defaultLowInputLatency;
    _inputDeviceParam.hostApiSpecificStreamInfo = NULL;

    _sampleRate = sampleRate;
    _frameLength = frameLength;
    const PaError err = Pa_OpenStream(&_dataStream, &_outputDeviceParam, NULL, _sampleRate, _frameLength, paClipOff, &QPortAudioPlayer::PortAudioCallback, this);
    if( err != paNoError ) {
         emit onError(err, Pa_GetErrorText(err));
         return false;
    }
    return true;
}

