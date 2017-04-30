#include "dsp.h"
#include <random>
#include <iostream>
#include <numeric>
#include <QDebug>

Real DSP::Acoustic::soundPropagationVelocity(Real temperatureCelcius) {
    static const Real gamma = 1.40;
    static const Real M = 28.9645e-3;
    static const Real factor = gamma *  arma::fdatum::R / M;
    const Real T = 273.15 + temperatureCelcius;
    return std::sqrt(factor * T);
}
/*
#include <sigpack/sigpack.h>
Vector DSP::Windowing::window(DSP::Windowing::SupportedWindow window, Size size) {
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
*/
QwtData DSP::hiperbolicChart(const Position& center, Real radius, Size size) {
    const Real x0 = center(0);
    const Real y0 = center(1);
    const Real residual = radius * radius - x0 * x0;

    const Size halfSize = size / 2;
    const Vector xPoints = arma::linspace(x0-radius, x0+radius, halfSize);
    QwtData chart(size);
    for (Size i=0; i<size; i++) {
        if (i < halfSize) {
            chart.yData(i) = y0 - std::sqrt(residual - xPoints(i)*xPoints(i) + 2*xPoints(i)*x0);
            chart.xData(i) = xPoints(i);
        } else {
            chart.yData(i) = y0 + std::sqrt(residual - xPoints(i-halfSize)*xPoints(i-halfSize) + 2*xPoints(i-halfSize)*x0);
            chart.xData(i) = xPoints(i-halfSize);
        }
    }
    return chart;
}



Vector DSP::rand(Real min, Real max, Size number) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<Real> distr(min, max);
    Vector random(number);
    Real* pointer = random.memptr();
    std::generate(pointer, pointer + number, [&](){ return distr(gen); });
    return random;
}

Real DSP::Parameter::energy(const Vector &data) {
    return  std::inner_product(data.begin(), data.end(), data.begin(), static_cast<Real>(0.0));
}



Real DSP::Parameter::power(const Vector &data) {
    return energy(data) / static_cast<Real>(data.size());
}
