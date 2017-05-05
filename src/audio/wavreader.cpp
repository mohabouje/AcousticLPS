#include "wavreader.h"
#include <QFile>
WavReader::Error WavReader::readFile(const QString filePath) {
    QFile file(filePath);
    if (!file.exists()) {
        return NotFound;
    }

    sf = sf_open(filePath.toStdString().data(), SFM_READ, &info);
    if (sf == NULL) {
        return NotSupported;
    }

    const int sampleCount = info.channels * info.channels;
    _buffer = new float[sampleCount];
    sf_read_float(sf, _buffer, sampleCount);
    sf_close(sf);
    return (_availableSamples == sampleCount) ? NoError : Partial;
}













