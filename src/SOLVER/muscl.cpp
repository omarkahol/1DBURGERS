#include "muscl.h"


double PDE::SOLVER::MUSCL_LINEAR(const PDE::IO::problem_data &data, double uPrevPrev, double uPrev, double u, double uNext, double uNextNext){

    // LEFT BOUNDARY
    double ul = uPrev + 0.5*data.limiter(uPrevPrev, uPrev, u)*(u - uPrev);
    double ur = u - 0.5*data.limiter(uPrev, u, uNext)*(uNext-u);
    double u_star = data.riemann_solver(ul, ur);
    double F1 = PDE::SOLVER::burgers_flux(u_star);
    
    // RIGHT BOUNDARY
    ul = u + 0.5*data.limiter(uPrev, u, uNext)*(uNext - u);
    ur = uNext - 0.5*data.limiter(u, uNext, uNextNext)*(uNextNext - uNext);
    u_star = data.riemann_solver(ul, ur);
    double F2 = PDE::SOLVER::burgers_flux(u_star);

    return F2-F1;

}


double PDE::SOLVER::MUSCL_PARABOLIC(const PDE::IO::problem_data &data, double uPrevPrev, double uPrev, double u, double uNext, double uNextNext) {
    //SLOPES
    double sigmaPrevPrev = uPrev-uPrevPrev;
    double sigmaPrev = u-uPrev;
    
    double sigmaNext = uNext -u;
    double sigmaNextNext = uNextNext-uNext;
    double k = 1.0/3.0;

    //LEFT BOUNDARY
    double ul = uPrev  + 0.25*data.limiter(uPrevPrev,uPrev,u)*((1-k)*sigmaPrevPrev+(1+k)*sigmaPrev);
    double ur = u - 0.25*data.limiter(uPrev,u,uNext)*((1-k)*sigmaNext+(1+k)*sigmaPrev);
    double u_star = data.riemann_solver(ul,ur);
    double F1 = PDE::SOLVER::burgers_flux(u_star);

    //RIGHT BOUNDARY
    ul = u  + 0.25*data.limiter(uPrev,u,uNext)*((1-k)*sigmaPrev+(1+k)*sigmaNext);
    ur = uNext - 0.25*data.limiter(u,uNext,uNextNext)*((1-k)*sigmaNextNext+(1+k)*sigmaNext);
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

double PDE::SOLVER::LAX_WENDROFF(const PDE::IO::problem_data &data,double uPrevPrev, double uPrev, double u, double uNext, double uNextNext){

    // LEFT BOUNDARY

    double ul = uPrev;
    double ur = u;
    double a = 0.5*(ur + ul);
    double F1_1 = 0.5*(PDE::SOLVER::burgers_flux(ul) + PDE::SOLVER::burgers_flux(ur)) - 0.5*a*(ur - ul);
    double F1_2 = 0.5*(PDE::SOLVER::burgers_flux(ul) + PDE::SOLVER::burgers_flux(ur));
    double F1 = F1_1 + data.limiter(uPrevPrev, uPrev, u)*(F1_2 - F1_1);

    // RIGHT BOUNDARY

    ul = u;
    ur = uNext;
    a = 0.5*(ur + ul);
    double F2_1 = 0.5*(PDE::SOLVER::burgers_flux(ul) + PDE::SOLVER::burgers_flux(ur)) - 0.5*a*(ur - ul);
    double F2_2 = 0.5*(PDE::SOLVER::burgers_flux(ul) + PDE::SOLVER::burgers_flux(ur));
    double F2 = F2_1 + data.limiter(uPrev, u, uNext)*(F2_2 - F2_1);

    return F2 - F1;

}

double PDE::SOLVER::KT(const PDE::IO::problem_data &data, double uPrevPrev, double uPrev, double u, double uNext, double uNextNext) {

    //SLOPES
    double sigmaPrevPrev = uPrev-uPrevPrev;
    double sigmaPrev = u-uPrev;
    
    double sigmaNext = uNext -u;
    double sigmaNextNext = uNextNext-uNext;
    double k = 1.0/3.0;

    //LEFT BOUNDARY
    double ul = uPrev  + 0.25*data.limiter(uPrevPrev,uPrev,u)*((1-k)*sigmaPrevPrev+(1+k)*sigmaPrev);
    double ur = u - 0.25*data.limiter(uPrev,u,uNext)*((1-k)*sigmaNext+(1+k)*sigmaPrev);
    double a = std::max(ur, ul);
    double F1 = 0.5*((PDE::SOLVER::burgers_flux(ur) + PDE::SOLVER::burgers_flux(ul)) - a*(ur - ul));

    //RIGHT BOUNDARY
    ul = u  + 0.25*data.limiter(uPrev,u,uNext)*((1-k)*sigmaPrev+(1+k)*sigmaNext);
    ur = uNext - 0.25*data.limiter(u,uNext,uNextNext)*((1-k)*sigmaNextNext+(1+k)*sigmaNext);
    a = std::max(ur, ul);
    double F2 = 0.5*((PDE::SOLVER::burgers_flux(ur) + PDE::SOLVER::burgers_flux(ul)) - a*(ur - ul));

    return F2-F1;

}