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

ChartData MathUtil::hiperbolicChart(const Position& center, Real radius, Real width, Size points) {
    const Real residual = radius * radius - center(0) * center(0);
    ChartData chart(points);
    chart.xData = arma::linspace(0.0, std::min(2.0 * radius, width), points);
    for (Size i=0; i<points; i++) {
        const Real x = chart.xData(i);
        chart.yData(i) = center(1) - std::sqrt(residual - x*x + 2*x*center(0));
    }
    return chart;
}


Vector MathUtil::quadraticEquationSolver(Real a, Real b, Real c) {
    static arma::vec::fixed<2> solutions;
    const Real d = std::sqrt(b*b - 4.0*a*c);
    solutions(0) = (-b + d) / (2.0 * a);
    solutions(1) = (-b - d) / (2.0 * a);
    return solutions;
}
