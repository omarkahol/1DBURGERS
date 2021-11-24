#if !defined(LW_CORRECTION_H)
#define LW_CORRECTION_H

#include <cmath>

namespace PDE::SOLVER {
    double wave(double ul, double ur);
    double correction(double ul, double ur, double CFL);

    //SLOPE LIMITER
    double van_leer(double uPrev, double u, double uNext);
    double superbee(double uPrev, double u, double uNext);
}



#endif // LW_CORRECTION_H
