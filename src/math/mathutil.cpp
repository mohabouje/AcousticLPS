#include "mathutil.h"
#include <sigpack/sigpack.h>

#include <QDebug>
Real MathUtil::soundPropagationVelocity(Real temperatureCelcius) {
    static const Real gamma = 1.40;
    static const Real M = 28.9645e-3;
    static const Real factor = gamma *  arma::fdatum::R / M;
    const Real T = 273.15 + temperatureCelcius;
    return std::sqrt(factor * T);
}

Vector MathUtil::window(MathUtil::SupportedWindow window, Size size) {
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


