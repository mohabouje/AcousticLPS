HEADERS += \
    $$PWD/trilateration.h \
    $$PWD/dsp.h \
    $$PWD/generalizedcrosscorrelation.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Bessel.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Biquad.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Butterworth.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Cascade.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/ChebyshevI.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/ChebyshevII.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Common.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Custom.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Design.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Dsp.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Elliptic.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Filter.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Layout.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Legendre.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/MathSupplement.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Params.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/PoleFilter.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/RBJ.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/RootFinder.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/SmoothedFilter.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/State.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Types.h \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/DspFilters/Utilities.h \
    $$PWD/algorithmtemplate.h \
    $$PWD/autocorrelation.h \
    $$PWD/powerspectraldensity.h

SOURCES += \
    $$PWD/trilateration.cpp \
    $$PWD/dsp.cpp \
    $$PWD/generalizedcrosscorrelation.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/Bessel.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/Biquad.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/Butterworth.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/Cascade.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/ChebyshevI.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/ChebyshevII.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/Custom.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/Design.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/Documentation.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/Elliptic.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/Filter.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/Legendre.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/Param.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/PoleFilter.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/RBJ.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/RootFinder.cpp \
    $$PWD/../dependencies/DSPFilters/shared/DSPFilters/source/State.cpp \
    $$PWD/algorithmtemplate.cpp \
    $$PWD/autocorrelation.cpp \
    $$PWD/powerspectraldensity.cpp

INCLUDEPATH += $$PWD/../dependencies/DSPFilters/shared/DSPFilters/include/

testing {
    SOURCES += $$PWD/test/qbeacontest.cpp \
        $$PWD/test/qtrilaterationtest.cpp \
        $$PWD/test/qmeasuretest.cpp

    RESOURCES += \
        $$PWD/test/resources.qrc
}


