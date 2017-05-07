#ifndef AUTOCORRELATION_H
#define AUTOCORRELATION_H

#include "algorithmtemplate.h"
#include <fftw3.h>
class Autocorrelation : public AlgorithmTemplate {
public:
    Autocorrelation();
    ~Autocorrelation();
    void setBufferSize(f_real sampleRate, f_real bufferTime);
    bool compute(const f_real *data, uint size);
private:
    fftwf_plan      _fft;
    fftwf_plan      _ifft;
    f_complex*      _complex;
};

#endif // AUTOCORRELATION_H
