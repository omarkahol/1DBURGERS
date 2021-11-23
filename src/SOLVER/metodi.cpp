#include "metodi.h"

// ul è u_j ; ur è u_j+1
double PDE::SOLVER::flux_upwind(double ul, double ur) { 
    return 0.5*ul*ul; 
}

double PDE::SOLVER::flux_godunov(double ul, double ur) {
    double F; 
    F = 0.5*ul*ul + ul*(ur - 0.5*(ul+ur)); 
    return F; 
}