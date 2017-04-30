#ifndef GENERALIZEDCROSSCORRELATION_H
#define GENERALIZEDCROSSCORRELATION_H
#include "dsp.h"
namespace DSP {
    class GeneralizedCrossCorrelation {
    public:
        enum Algorithm { Standard = 0, Phat, MaximumLikelihood };
        GeneralizedCrossCorrelation(Algorithm algo = Standard);
        Vector compute(const Vector&, const Vector&, Algorithm algorithm = Standard);
        Vector delay(const Vector& vector, Size delay);
    private:
        Algorithm   _algorithm{Standard};
        Vector computePhat(const Vector&, const Vector&);
        Vector computeMaximumLikelihood(const Vector&, const Vector&);
        Vector computeStandard(const Vector &original, const Vector &delayed);
    };
}


#endif // GENERALIZEDCROSSCORRELATION_H
