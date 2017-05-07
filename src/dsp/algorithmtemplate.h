#ifndef ALGORITHMTEMPLATE_H
#define ALGORITHMTEMPLATE_H

#include <complex>
using f_real      = float;
using f_complex   = std::complex<float>;
using uint        = unsigned int;
class AlgorithmTemplate {
public:
    AlgorithmTemplate() {}
    ~AlgorithmTemplate() {
        delete[] _input;
        delete[] _output;
    }

    virtual void setBufferSize(f_real sampleRate, f_real bufferTime) = 0;
    virtual bool compute(const f_real* data, uint size) = 0;

    inline f_real* input() const { return _input; }
    inline uint   inputSize() const { return _inputSize; }
    inline f_real* output() const { return _output; }
    inline uint   outputSize() const { return _outputSize; }
protected:
    uint            _inputSize;
    uint            _outputSize;
    f_real*          _input;
    f_real*          _output;
};

#endif // ALGORITHMTEMPLATE_H
