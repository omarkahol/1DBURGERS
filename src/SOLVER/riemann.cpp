#include "riemann.h"



double PDE::SOLVER::godunov(double ul, double ur) {
    double s = 0.5*(ul+ur);
    if (ul > ur) { // SHOCK CASE

        if (s>0) { //UPWIND PROPAGATION
            return ul;
        } else { //DOWNWIND PROPAGATION
            return ur;
        }

    } else { //RAREFACTION FAN CASE
        if (ul < 0 && ur > 0) { //SONIC CASE
           return 0.0;
        } else if (ul > 0) { //FAN THAT PROPAGATES UPWIND
            return ul;
        } else { //FAN THAT PROPAGATES DOWNWIND
            return ur;
        }
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