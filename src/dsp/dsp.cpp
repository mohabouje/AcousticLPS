#include "dsp.h"
#include <random>
#include <iostream>
#include <numeric>
#include <QDebug>

Real DSP::Acoustic::soundPropagationVelocity(Real temperatureCelcius) {
    static const Real gamma = 1.40;
    static const Real M = 28.9645e-3;
    static const Real factor = gamma *  arma::fdatum::R / M;
    const Real T = 273.15 + temperatureCelcius;
    return std::sqrt(factor * T);
}
/*
Vector DSP::Windowing::window(DSP::Windowing::SupportedWindow window, Size size) {
    Vector vect;
    switch (window) {
    case HammingWindow:
        vect = sp::hamming(size);
    case HannWindow:
        vect = sp::hann(size);
    case HanningWindow:
        vect = sp::hanning(size);
    case  BlackmanWindow:
        vect = sp::blackman(size);
    case  FlattopWindow:
        vect = sp::flattopwin(size);
    case TriangWindow:
        vect = sp::triang(size);
    default:
        vect = sp::hamming(size);
    }
    return vect;
}
*/



Real DSP::Math::energy(const Vector &data) {
    return  std::inner_product(data.begin(), data.end(), data.begin(), static_cast<Real>(0.0));
}



Real DSP::Math::power(const Vector &data) {
    return energy(data) / static_cast<Real>(data.size());
}

Size DSP::Math::nextPow2(int x) {
    if (x < 0)
        return 0;
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x+1;
}

Vector DSP::Timming::delay(const Vector &original, uint sampleRate, Real time) {
    const uint samples = sampleRate * time;
    return delay(original, samples);
}

Vector DSP::Timming::delay(const Vector &original, uint delay) {
    const uint size = original.size();
    Vector tmp(size, arma::fill::randn);
    for (uint i = delay; i<size; i++) {
        tmp[i] = original[i-delay];
    }
    return tmp;
}
