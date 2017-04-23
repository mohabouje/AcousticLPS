HEADERS += \
    $$PWD/qbeacon.h \
    $$PWD/qtrilateration.h \
    $$PWD/qmeasure.h

SOURCES += \
    $$PWD/qbeacon.cpp \
    $$PWD/qtrilateration.cpp \
    $$PWD/qmeasure.cpp

testing {
    SOURCES += $$PWD/test/qbeacontest.cpp \
        $$PWD/test/qtrilaterationtest.cpp \
        $$PWD/test/qmeasuretest.cpp

    RESOURCES += \
        $$PWD/test/resources.qrc
}


