#include "metodi.h"

// ul è u_j ; ur è u_j+1
double PDE::SOLVER::flux_upwind(double ul, double ur) { 
    return 0.5*ul*ul; 
}

double PDE::SOLVER::flux_godunov(double ul, double ur) {
    double F;
    if (ul > 0 && 0.5*(ul+ur)>0) {
        F = 0.5*ul*ul;
    } else if (ur < 0 && 0.5*(ul+ur)<0){
        F = 0.5*ur*ur;
    } else {
        F = 0.0;
    }
    return F; 
}