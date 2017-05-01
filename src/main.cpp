#if TESTING_ENABLED
#include <catch_with_main.hpp>
#else
#include "config.h"
#include "mainwindow.h"

#include <gui/helper.h>
#include <dsp/generalizedcrosscorrelation.h>
#include <QDebug>
#include <QApplication>

#define TEST_SOURCE 0

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName(APP_NAME);
    a.setApplicationVersion(APP_VERSION);
    a.setOrganizationName(ORGANIZATION_NAME);
    a.setOrganizationDomain(ORGANIZATION_DOMAIN);
#if TEST_SOURCE
    const Real F0 = 3;
    const Real Fs = 20;
    const Size samples = 4 * Fs;

    Vector vect(samples);
    for (Size i=0; i<samples; i++) {
        vect(i) = 5 * sin(2*arma::datum::pi*F0/Fs*i);
    }

    const Vector delayed = DSP::Timming::delay(vect, Fs, 0.5);


    arma::arma_version ver;
    std::cout << "ARMA version: "<< ver.as_string() << std::endl;

    DSP::GeneralizedCrossCorrelation GCC;
    Gui::plot(GCC.compute(vect, vect));
    Gui::plot(GCC.compute(vect, delayed, DSP::GeneralizedCrossCorrelation::Phat));

#else
    MainWindow w;
    w.show();
#endif

    return a.exec();
}
#endif

