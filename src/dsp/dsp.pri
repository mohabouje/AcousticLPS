HEADERS += \
    $$PWD/trilateration.h \
    $$PWD/dsp.h

SOURCES += \
    $$PWD/trilateration.cpp \
    $$PWD/dsp.cpp

testing {
    SOURCES += $$PWD/test/qbeacontest.cpp \
        $$PWD/test/qtrilaterationtest.cpp \
        $$PWD/test/qmeasuretest.cpp

    RESOURCES += \
        $$PWD/test/resources.qrc
}


