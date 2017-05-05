#include "qportaudiodevice.h"
QPortAudioDevice::QPortAudioDevice(QObject *parent) : QObject(parent) {
}

bool QPortAudioDevice::setSampleRate(double sampleRate) {
    if ((isSampleRateSupported(sampleRate) == PaErrorCode::paNoError)) {
        return restartDevice(currentDevice(), sampleRate, frameLength());
    }
    return false;
}

bool QPortAudioDevice::setFrameLength(unsigned long frameLength) {
    _frameLength = frameLength;
    restartDevice(currentDevice(), sampleRate(), frameLength);
    return true;
}


int QPortAudioDevice::PortAudioCallback(const void *inputBuffer,
                                        void *outputBuffer,
                                        unsigned long framesPerBuffer,
                                        const PaStreamCallbackTimeInfo *timeInfo,
                                        PaStreamCallbackFlags statusFlags,
                                        void *userData)
{
    return ((QPortAudioDevice*)userData)->bufferReady(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags);
}
