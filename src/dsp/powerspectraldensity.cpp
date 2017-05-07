#include "powerspectraldensity.h"
#include <dsp/dsp.h>
PowerSpectralDensity::PowerSpectralDensity()
{

}

PowerSpectralDensity::~PowerSpectralDensity() {
    delete[] _complex;
    fftwf_destroy_plan(_fft);
}

void PowerSpectralDensity::setBufferSize(f_real sampleRate, f_real bufferTime) {
    _inputSize = static_cast<uint>(sampleRate * bufferTime);
    const uint fftSize = static_cast<uint>(DSP::Math::nextPow2(_inputSize));

    _complex = new f_complex[fftSize]{f_complex(0.,0.)};
    _input = new f_real[fftSize]{0};
    _outputSize = fftSize / 2 + 1;
    _output = new f_real[_outputSize]{0};

    _fft = fftwf_plan_dft_r2c_1d(fftSize, _input, reinterpret_cast<fftwf_complex*>(_complex), FFTW_ESTIMATE);
}

bool PowerSpectralDensity::compute(const f_real *data, uint size) {
    std::memcpy(_input, data, size);
    fftwf_execute(_fft);
    for (uint i=0; i<_outputSize; i++) {
        _output[i] = 20.0 * std::log10(std::abs(_complex[i]));
    }
}
