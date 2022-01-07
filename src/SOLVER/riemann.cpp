#include "riemann.h"



double PDE::SOLVER::godunov(double ul, double ur) {
    double s = 0.5*(ul+ur);
    if (ul >= 0 && s >=0) {
        return ul;
    } else if (ur >= 0 && s <= 0) {
        return ur;
    } else {
        return 0.0;
    }
}

double PDE::SOLVER::roe_fix(double ul, double ur) {
    double um = 0.5*(ul+ur); //SONIC ENTROPY FIX
    if (ul > 0) { //UPWIND DISCONTINUITY
       return ul;
    } else if (ul < 0 && ur > 0) { //SONIC CASE
        return um;
    } else { //DOWNWIND DISCONTINUITY
        return ur;
    }
}


double PDE::SOLVER::burgers_flux(double u) {
    return 0.5*u*u;
}