#ifndef CONFIG_H
#define CONFIG_H


#define APP_NAME            "Acoustic LPS"
#define APP_VERSION         "0.0"
#define ORGANIZATION_DOMAIN "www.ugr.es"
#define ORGANIZATION_NAME   "Universidad de Granada"

#define ENVIRONEMENT_FORMAT   ".envi"
#define ENVIRONEMENT_FILENAME "environement" ENVIRONEMENT_FORMAT


#include <armadillo>
using Real = double;
using Size = arma::uword;
using Vector = arma::vec;
using Matrix = arma::mat;
using Position = arma::vec::fixed<3>;



#endif // CONFIG_H
