HEADERS += \
    $$PWD/../dependencies/trilateration/navigation/trilateteration/src/beacon.h \
    $$PWD/../dependencies/trilateration/navigation/trilateteration/src/trilateration.h \
    $$PWD/qbeacon.h

SOURCES += \
    $$PWD/../dependencies/trilateration/navigation/trilateteration/src/beacon.cpp \
    $$PWD/../dependencies/trilateration/navigation/trilateteration/src/trilateration.cpp \
    $$PWD/qbeacon.cpp


# For quick include, add dependencies as dependency path.
INCLUDEPATH += $$PWD/../dependencies/trilateration/navigation/trilateteration/src/
DEPENDPATH +=  $$PWD/../dependencies/trilateration/navigation/trilateteration/src/

testing {
    SOURCES += $$PWD/test/qbeacontest.cpp
}
