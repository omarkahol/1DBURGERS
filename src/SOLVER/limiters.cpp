#include "limiters.h"


double PDE::SOLVER::minmod(double a, double b) {
    if(a*b>0 && std::abs(a)<std::abs(b)) {
        return a;
    } else if(a*b>0 && std::abs(a)>std::abs(b)) {
        return b;
    } else {
        return 0;
    }
}
