#ifndef ALGORITHMTEMPLATE_H
#define ALGORITHMTEMPLATE_H


#include <QtCore>
class AlgorithmTemplate {
public:
    AlgorithmTemplate() {}
    virtual void setInput(const float* data, uint size) = 0;
    virtual bool compute() = 0;

    inline float* input() const { return _input; }
    inline uint   inputSize() const { return _inputSize; }
    inline float* output() const { return _output; }
    inline uint   outputSize() const { return _outputSize; }
protected:
    uint            _inputSize;
    uint            _outputSize;
    float*          _input;
    float*          _output;
};

#endif // ALGORITHMTEMPLATE_H
