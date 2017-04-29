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
using Complex = arma::cx_vec;
using Matrix = arma::mat;
using Position = arma::vec::fixed<3>;

struct QwtData {
    QwtData(Size size) {
        xData = Vector(size);
        yData = Vector(size);
    }
    void reset() {
        xData.reset();
        yData.reset();
    }
    inline const double* x() const { return xData.memptr(); }
    inline const double* y() const { return yData.memptr(); }
    inline Size size() const { return xData.size(); }
    Vector xData;
    Vector yData;
};

#endif // CONFIG_H
