#include "generalizedcrosscorrelation.h"
#include <cfloat>
#include <QDebug>
using namespace DSP;
GeneralizedCrossCorrelation::GeneralizedCrossCorrelation() {}

Vector GeneralizedCrossCorrelation::compute(const Vector &original, const Vector &delayed, Algorithm algoritm) {
    switch (algoritm) {
    case Phat:
        return computePhat(original, delayed);
    case Standard:
    default:
        return computeStandard(original, delayed);
    }
}

Vector GeneralizedCrossCorrelation::computeStandard(const Vector &original, const Vector &delayed) {
    const Size fftSize = static_cast<Size>(Parameter::nextPow2(2*original.size()-1));
    return arma::real(arma::ifft(arma::fft(original, fftSize) % arma::conj(arma::fft(delayed, fftSize))));
}

Vector GeneralizedCrossCorrelation::computePhat(const Vector &original, const Vector &delayed) {
    const Size fftSize = static_cast<Size>(Parameter::nextPow2(2*original.size()-1));
    Complex Cxy = arma::fft(original, fftSize) % arma::conj(arma::fft(delayed, fftSize));
    return arma::real(arma::ifft(-Cxy / arma::abs(Cxy)));
}

