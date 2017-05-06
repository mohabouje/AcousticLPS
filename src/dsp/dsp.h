#include "config.h"
namespace DSP {
    namespace Timming {
        Vector delay(const Vector &original, uint sampleRate, Real time);
        Vector delay(const Vector& original, uint delay);
    }

    namespace Windowing {
        enum SupportedWindow { HammingWindow = 0, HannWindow, HanningWindow, BlackmanWindow, FlattopWindow, TriangWindow};
        //Vector window(SupportedWindow window, Size size);
    }

    namespace Acoustic {
        Real soundPropagationVelocity(Real temperatureCelcius);

    }

    namespace Math {
        Size nextPow2(int value);
        Real energy(const Vector& data);
        Real power(const Vector& data);
    }
}

