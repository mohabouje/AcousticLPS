#include "generalizedcrosscorrelation.h"

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
    return Vector();
}

Vector GeneralizedCrossCorrelation::computeMaximumLikelihood(const Vector &original, const Vector &delayed) {
    return Vector();
}
