#include "qportaudiorecorder.h"

QPortAudioRecorder::QPortAudioRecorder(QObject *parent) : QObject(parent) {

}

PaStreamCallbackResult QPortAudioRecorder::bufferReady(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags)
{
    return paContinue;
}
