#include "limiters.h"


double PDE::SOLVER::vanAlabada(double uPrev,double u, double uNext) {
    double theta = (std::abs(uNext-u)<1e-10)?1.0:(u-uPrev)/(uNext-u);
    return 2*theta/(1+theta*theta);
}
