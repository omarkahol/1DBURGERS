#include "muscl.h"


double PDE::SOLVER::MUSCL(const PDE::IO::problem_data &data, double uPrevPrev, double uPrev, double u, double uNext, double uNextNext) {
    //SLOPES
    double sigmaPrevPrev = uPrev-uPrevPrev;
    double sigmaPrev = u-uPrev;
    
    double sigmaNext = uNext -u;
    double sigmaNextNext = uNextNext-uNext;
    double k = 1.0/3.0;

    //LEFT BOUNDARY
    double ul = uPrev  + 0.25*PDE::SOLVER::vanAlabada(uPrevPrev,uPrev,u)*((1-k)*sigmaPrevPrev+(1+k)*sigmaPrev);
    double ur = u - 0.25*PDE::SOLVER::vanAlabada(uPrev,u,uNext)*((1-k)*sigmaNext+(1+k)*sigmaPrev);;
    double u_star = data.riemann_solver(ul,ur);
    double F1 = PDE::SOLVER::burgers_flux(u_star);

    //RIGHT BOUNDARY
    ul = u  + 0.25*PDE::SOLVER::vanAlabada(uPrev,u,uNext)*((1-k)*sigmaPrev+(1+k)*sigmaNext);
    ur = uNext - 0.25*PDE::SOLVER::vanAlabada(u,uNext,uNextNext)*((1-k)*sigmaNextNext+(1+k)*sigmaNext);
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