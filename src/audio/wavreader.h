#ifndef WAVREADER_H
#define WAVREADER_H

#include <QString>
#include <sndfile.h>
class WavReader {
public:
    WavReader() {}
    enum Error { NoError, NotFound, NotSupported, Partial };
    Error readFile(const QString filePath);
    inline float *buffer() const { return _buffer; }
    inline int channelCount() const { return info.channels; }
    inline int frameCount() const { return info.frames; }
    inline int sampleRate() const { return info.samplerate; }
    inline int sampleCount() const { return info.channels * info.channels;}
    inline int availableSamples() const { return _availableSamples; }
private:
    SNDFILE *sf;
    SF_INFO info;
    float* _buffer;
    int _availableSamples;
};

#endif // WAVREADER_H
