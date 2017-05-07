#ifndef POWERSPECTRALDENSITY_H
#define POWERSPECTRALDENSITY_H

#include "algorithmtemplate.h"
#include <fftw3.h>
class PowerSpectralDensity : public AlgorithmTemplate {
public:
    PowerSpectralDensity();
    ~PowerSpectralDensity();
    void setBufferSize(f_real sampleRate, f_real bufferTime);
    bool compute(const f_real *data, uint size);
private:
    fftwf_plan          _fft;
    f_complex*          _complex;
};

#endif // POWERSPECTRALDENSITY_H
