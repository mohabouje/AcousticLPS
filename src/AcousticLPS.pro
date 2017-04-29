#-------------------------------------------------
#
# Project created by QtCreator 2017-04-22T18:54:20
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
CONFIG += c++11
CONFIG += no_testing
#CONFIG += testing
DEFINES += QT_DEPRECATED_WARNINGS


no_testing {
    TARGET = AcousticLPS
    DEFINES += "TESTING_ENABLED=0"
}

testing {
    QT += testlib
    SOURCES -= main.cpp
    TARGET = TestAcousticLPS
    DEFINES += "TESTING_ENABLED=1"
    INCLUDEPATH += $$PWD/dependencies/catch/include
}

SOURCES += main.cpp \
        mainwindow.cpp \

HEADERS  += mainwindow.h \
    config.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

DEFINES += ARMA_DONT_USE_WRAPPER
DEFINES += HAVE_FFTW


# Using Armadillo + OpenBlas for ALgebra operation
# How to install?  => http://www.uio.no/studier/emner/matnat/fys/FYS4411/v13/guides/installing-armadillo/
LIBS += -llapack -lblas -larmadillo

# Using QWT to mathematical graphics.
LIBS += -L$$PWD/../../../../../../usr/local/qwt-6.1.3/lib/ -lqwt
INCLUDEPATH += $$PWD/../../../../../../usr/local/qwt-6.1.3/include
DEPENDPATH += $$PWD/../../../../../../usr/local/qwt-6.1.3/include
CONFIG += qwt

# Using protocol buffers to export/import configurations.
LIBS += -lprotobuf
QMAKE_CFLAGS += protobuf

# Using FFTW library
LIBS += -lfftw3

# Include de different submodules
include("./math/math.pri")
include("./gui/gui.pri")
include("./model/model.pri")
include("./util/util.pri")
include("./sigpack/sigpack.pri")



