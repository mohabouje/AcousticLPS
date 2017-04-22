INCLUDEPATH += $$PWD/../dependencies/uuid/include/boost
DEPENDPATH +=  $$PWD/../dependencies/uuid/include/boost

INCLUDEPATH += $$PWD/../dependencies/trilateration/navigation/trilateteration/src/
DEPENDPATH +=  $$PWD/../dependencies/trilateration/navigation/trilateteration/src/

HEADERS += \
    $$PWD/../dependencies/trilateration/navigation/trilateteration/src/beacon.h \
    $$PWD/../dependencies/trilateration/navigation/trilateteration/src/trilateration.h \
    $$PWD/qbeacon.h

SOURCES += \
    $$PWD/../dependencies/trilateration/navigation/trilateteration/src/beacon.cpp \
    $$PWD/../dependencies/trilateration/navigation/trilateteration/src/trilateration.cpp \
    $$PWD/qbeacon.cpp


