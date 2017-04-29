#include "config.h"
namespace MathUtil {
    enum SupportedWindow { HammingWindow = 0, HannWindow, HanningWindow, BlackmanWindow, FlattopWindow, TriangWindow};
    Real soundPropagationVelocity(Real temperatureCelcius);
    Vector window(SupportedWindow window, Size size);
}

