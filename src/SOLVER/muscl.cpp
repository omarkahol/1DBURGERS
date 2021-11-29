#include "muscl.h"


double PDE::SOLVER::MUSCL(const PDE::IO::problem_data &data, double uPrevPrev, double uPrev, double u, double uNext, double uNextNext) {
    //SLOPES
    double sigmaPrev = PDE::SOLVER::minmod(u-uPrev,uPrev-uPrevPrev);
    double sigma = PDE::SOLVER::minmod(uNext-u,u-uPrev);
    double sigmaNext = PDE::SOLVER::minmod(uNextNext-uNext,uNext-u);

    //LEFT BOUNDARY
    double ul = uPrev  + 0.5*sigmaPrev;
    double ur = u - 0.5*sigma;
    double u_star = data.riemann_solver(ul,ur);
    double F1 = PDE::SOLVER::burgers_flux(u_star);

    //RIGHT BOUNDARY
    ul = u  + 0.5*sigma;
    ur = uNext - 0.5*sigmaNext;
    u_star = data.riemann_solver(ul,ur);
    double F2 = PDE::SOLVER::burgers_flux(u_star);

    return F2-F1;
}

double PDE::SOLVER::UPWIND(const PDE::IO::problem_data &data, double uPrev, double u, double uNext) {
    double u_star = data.riemann_solver(uPrev,u);
    double F1 = PDE::SOLVER::burgers_flux(u_star);

    u_star = data.riemann_solver(u,uNext);
    double F2 = PDE::SOLVER::burgers_flux(u_star);
    return F2-F1;
}