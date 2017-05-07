#include "autocorrelation.h"
#include <algorithm>
#include <cstring>
Autocorrelation::Autocorrelation()
{

}

Autocorrelation::~Autocorrelation() {
    delete[] _complex;
    fftwf_destroy_plan(_fft);
    fftwf_destroy_plan(_ifft);
}

void Autocorrelation::setBufferSize(f_real sampleRate, f_real bufferTime) {
    _inputSize = static_cast<uint>(sampleRate * bufferTime);
    _outputSize = static_cast<uint>(2 * _inputSize - 1);

    _complex = new f_complex[_outputSize];
    _input = new f_real[_outputSize]{0};
    _output = new f_real[_outputSize]{0};

    _fft = fftwf_plan_dft_r2c_1d(_outputSize, _input, reinterpret_cast<fftwf_complex*>(_complex), FFTW_ESTIMATE);
    _ifft = fftwf_plan_dft_c2r_1d(_outputSize, reinterpret_cast<fftwf_complex*>(_complex), _output, FFTW_ESTIMATE);
}

bool Autocorrelation::compute(const f_real *data, uint size) {
    std::memcpy(_input, data, size);

    fftwf_execute(_fft);
    for (uint i = 0;  i< _outputSize; i++) {
        _complex[i] = _complex[i] * std::conj(_complex[i]);
    }
    fftwf_execute(_ifft);
    const float _max = *std::max_element(_output, _output + _outputSize);
    std::for_each(_output, _output + _outputSize, [&_max](f_real& value) {
        value /= _max;
    });
}

