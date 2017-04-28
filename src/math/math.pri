HEADERS += \
    $$PWD/qtrilateration.h \

SOURCES += \
    $$PWD/qtrilateration.cpp \

testing {
    SOURCES += $$PWD/test/qbeacontest.cpp \
        $$PWD/test/qtrilaterationtest.cpp \
        $$PWD/test/qmeasuretest.cpp

    RESOURCES += \
        $$PWD/test/resources.qrc
}


