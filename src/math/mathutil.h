#include "config.h"
namespace MathUtil {
    enum SupportedWindow { HammingWindow = 0, HannWindow, HanningWindow, BlackmanWindow, FlattopWindow, TriangWindow};
    ChartData hiperbolicChart(const Position& center, Real radius, Real width, Size points);
    Vector quadraticEquationSolver(Real a, Real b, Real c);
    Real soundPropagationVelocity(Real temperatureCelcius);
    Vector window(SupportedWindow window, Size size);
}

