#if !defined(RIEMANN_H)
#define RIEMANN_H

namespace PDE::SOLVER {
    double godunov(double ul, double ur);
    double roe_fix(double ul, double ur);
    double roe(double ul, double ur);
    double burgers_flux(double u);
}

#endif
