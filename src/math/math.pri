HEADERS += \
    $$PWD/trilateration.h \
    $$PWD/mathutil.h

SOURCES += \
    $$PWD/trilateration.cpp \
    $$PWD/mathutil.cpp

testing {
    SOURCES += $$PWD/test/qbeacontest.cpp \
        $$PWD/test/qtrilaterationtest.cpp \
        $$PWD/test/qmeasuretest.cpp

    RESOURCES += \
        $$PWD/test/resources.qrc
}


