#include "lw_correction.h"

double PDE::SOLVER::wave(double ul, double ur) {
    return ur-ul;
}
double PDE::SOLVER::correction(double ul, double ur, double CFL) {
    return 0.5*std::abs(ul)*(1-CFL)*PDE::SOLVER::wave(ul,ur);
}

double PDE::SOLVER::van_leer(double uPrev, double u, double uNext) {
    double theta = (u-uPrev)/(uNext-u);
    return (theta + std::abs(theta))/(1+std::abs(theta));
}

double PDE::SOLVER::superbee(double uPrev, double u, double uNext) {
    double theta = (u-uPrev)/(uNext-u);
    return std::max(std::max(0.0,std::min(1.0,2*theta)),std::min(2.0,theta));
}