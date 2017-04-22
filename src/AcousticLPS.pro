#-------------------------------------------------
#
# Project created by QtCreator 2017-04-22T18:54:20
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
CONFIG += c++11
#CONFIG += no_testing
CONFIG += testing


no_testing {
    TARGET = AcousticLPS
    DEFINES += "TESTING_ENABLED=0"
}

testing {
    QT += testlib
    TARGET = TestAcousticLPS
    DEFINES += "TESTING_ENABLED=1"
    INCLUDEPATH += $$PWD/dependencies/catch/include
}

SOURCES += main.cpp \
        mainwindow.cpp \

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui



DEFINES += QT_DEPRECATED_WARNINGS



# Include de different submodules
include("./trilateration/trilateration.pri")

