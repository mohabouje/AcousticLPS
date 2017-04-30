#ifndef GENERALIZEDCROSSCORRELATION_H
#define GENERALIZEDCROSSCORRELATION_H
#include "config.h"
namespace DSP {
    class GeneralizedCrossCorrelation {
    public:
        enum Algorithm { Standard = 0, Phat, MaximumLikelihood };
        GeneralizedCrossCorrelation(Algorithm algo = Standard);
        Vector compute(const Vector&, const Vector&, Algorithm algorithm = Standard);
    private:
        Algorithm   _algorithm{Standard};
        Vector computePhat(const Vector&, const Vector&);
        Vector computeMaximumLikelihood(const Vector&, const Vector&);
    };
}


#endif // GENERALIZEDCROSSCORRELATION_H
