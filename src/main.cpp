#if TESTING_ENABLED
#include <catch_with_main.hpp>
#else
#include "config.h"
#include "mainwindow.h"

#include <gui/helper.h>
#include <QApplication>
#include <dsp/generalizedcrosscorrelation.h>
#include <QDebug>

#define TEST_SOURCE 1

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

    DSP::GeneralizedCrossCorrelation GCC;
    const Vector delayed = GCC.delay(vect, Fs*0.5);

    //Gui::plot(spectral);

   /*Gui::plot(vect);
    Gui::plot(delayed);*/

    arma::arma_version ver;
    std::cout << "ARMA version: "<< ver.as_string() << std::endl;


    Gui::plot(GCC.compute(vect, vect));
    Gui::plot(GCC.compute(vect, vect, DSP::GeneralizedCrossCorrelation::Phat));

#elif
    MainWindow w;
    w.show();
#endif

    return a.exec();
}
#endif

