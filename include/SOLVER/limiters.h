#if !defined(LIMITERS_H)
#define LIMITERS_H

#include <cmath>

namespace PDE::SOLVER {
    double vanAlbada(double, double, double);
    double vanLeer(double, double, double);
    double superbee(double, double, double);
    double minmod(double, double, double);
    
}



#endif
