#include "generalizedcrosscorrelation.h"
#include <sigpack/sigpack.h>

using namespace DSP;
GeneralizedCrossCorrelation::GeneralizedCrossCorrelation(Algorithm algo) : _algorithm(algo) {

}

Vector GeneralizedCrossCorrelation::compute(const Vector &original, const Vector &delayed, Algorithm algoritm) {
    switch (algoritm) {
    case Standard:
        return arma::cor(original, delayed);
    case Phat:
        return computePhat(original, delayed);
    case MaximumLikelihood:
        return computeMaximumLikelihood(original, delayed);
    default:
        return arma::cor(original, delayed);
    }

}

Vector GeneralizedCrossCorrelation::computePhat(const Vector &original, const Vector &delayed) {
    static const Size MinSize = 1024;
    const Size nSamples = std::max(original.size(), MinSize);
    const Complex X = arma::fft(original, nSamples);
    const Complex Y = arma::fft(delayed, nSamples);
    const Complex Cxy = X * arma::conj(Y);
    Complex R = Cxy / arma::abs(Cxy);
    sp::FFTW tmp = sp::FFTW(MinSize);
    return tmp.ifft(R);
}

Vector GeneralizedCrossCorrelation::computeMaximumLikelihood(const Vector &original, const Vector &delayed) {
    return Vector();
}
