#include "mathutil.h"
#include <sigpack/sigpack.h>
Real MathUtil::soundPropagationVelocity(Real temperatureCelcius) {
    static const Real gamma = 1.40;
    static const Real M = 28.9645e-3;
    static const Real factor = gamma *  arma::fdatum::R / M;
    const Real T = 273.15 + temperatureCelcius;
    return std::sqrt(factor * T);
}

Vector MathUtil::window(MathUtil::SupportedWindow window, Size size) {
    switch (window) {
    case HammingWindow:
        return sp::hamming(size);
    case HannWindow:
        return sp::hann(size);
    case HanningWindow:
        return sp::hanning(size);
    case  BlackmanWindow:
        return sp::blackman(size);
    case  FlattopWindow:
        return sp::flattopwin(size);
    case TriangWindow:
        return sp::triang(size);
    default:
        return sp::hamming(size);
    }
}
