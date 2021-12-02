#include "limiters.h"


double PDE::SOLVER::vanAlbada(double uPrev,double u, double uNext) {
    double theta = (std::abs(uNext-u)<1e-10)?1.0:(u-uPrev)/(uNext-u);
    return (theta*theta + theta)/(theta*theta + 1);
}
/*double PDE::SOLVER::vanLeer(double uPrev,double u, double uNext) {
    double theta = (std::abs(uNext-u)<1e-10)?1.0:(u-uPrev)/(uNext-u);
    return (theta + std::abs(theta))/(1 + std::abs(theta));
}
double PDE::SOLVER::superbee(double uPrev,double u, double uNext) {
    double theta = (std::abs(uNext-u)<1e-10)?1.0:(u-uPrev)/(uNext-u);
    return std::max(0.0,std::max(std::min(2*theta,1.0),std::min(theta,2.)));
}
double PDE::SOLVER::minmod(double uPrev,double u, double uNext) {
    double theta = (std::abs(uNext-u)<1e-10)?1.0:(u-uPrev)/(uNext-u);
    return std::max(0.,std::min(1.,theta));
}*/