#ifndef CONFIG_H
#define CONFIG_H

#define ARMA_DONT_USE_WRAPPER
#include <armadillo>

#ifdef DOUBLE_PRECISION


#else
static constexpr int CoordinatesCount{3};
using Real = float;
using Vector = arma::fvec;
using Matrix = arma::fmat;
using Position = arma::vec::fixed<CoordinatesCount>;
#endif



#endif // CONFIG_H
