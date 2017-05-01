#include "generalizedcrosscorrelation.h"
#include <sigpack/sigpack.h>
#include <cfloat>
#include <QDebug>
using namespace DSP;
GeneralizedCrossCorrelation::GeneralizedCrossCorrelation(Algorithm algo) : _algorithm(algo) {

}

Vector GeneralizedCrossCorrelation::compute(const Vector &original, const Vector &delayed, Algorithm algoritm) {
    switch (algoritm) {
    case Standard:
        return computeStandard(original, delayed);
    case Phat:
        return computePhat(original, delayed);
    case MaximumLikelihood:
        return computeMaximumLikelihood(original, delayed);
    default:
        return computeStandard(original, delayed);
    }

}

Vector GeneralizedCrossCorrelation::delay(const Vector &vector, Size delay) {
    sp::Delay<Real> op = sp::Delay<Real>(delay);
    return op.delay(vector);
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

Vector GeneralizedCrossCorrelation::computeMaximumLikelihood(const Vector &original, const Vector &delayed) {
    return Vector();
}
