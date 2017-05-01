#ifndef GENERALIZEDCROSSCORRELATION_H
#define GENERALIZEDCROSSCORRELATION_H
#include "dsp.h"
namespace DSP {
    class GeneralizedCrossCorrelation {
    public:
        enum Algorithm { Standard = 0, Phat};
        GeneralizedCrossCorrelation();
        static Vector compute(const Vector&, const Vector&, Algorithm algorithm = Standard);
    private:
        static Vector computePhat(const Vector&, const Vector&);
        static Vector computeStandard(const Vector &original, const Vector &delayed);
    };
}


#endif // GENERALIZEDCROSSCORRELATION_H
