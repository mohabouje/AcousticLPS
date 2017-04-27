#ifndef CONFIG_H
#define CONFIG_H

#define ARMA_DONT_USE_WRAPPER
#include <armadillo>

#define APP_NAME            "Acoustic LPS"
#define APP_VERSION         "0.0"
#define ORGANIZATION_DOMAIN "www.ugr.es"
#define ORGANIZATION_NAME   "Universidad de Granada"

#define ENVIRONEMENT_FORMAT   ".envi"
#define ENVIRONEMENT_FILENAME "environement" ENVIRONEMENT_FORMAT


#ifdef DOUBLE_PRECISION


#else
static constexpr int CoordinatesCount{3};
using Real = float;
using Vector = arma::fvec;
using Matrix = arma::fmat;
using Position = arma::vec::fixed<CoordinatesCount>;
#endif



#endif // CONFIG_H
