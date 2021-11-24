#if !defined(FLUXES_H)
#define FLUXES_H

namespace PDE::SOLVER {
    double flux_upwind(double ul, double ur);
    double flux_godunov(double ul, double ur);
}

#endif
