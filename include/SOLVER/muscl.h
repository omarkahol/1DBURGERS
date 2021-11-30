#if !defined(MUSCL_H)
#define MUSCL_H

#include "limiters.h"
#include "riemann.h"
#include "problem_data.h"

namespace PDE::SOLVER {
    double MUSCL_PARABOLIC(const PDE::IO::problem_data &data,double uPrevPrev, double uPrev, double u, double uNext, double uNextNext);
    double UPWIND(const PDE::IO::problem_data &data, double uPrev, double u, double uNext);
    double KT(const PDE::IO::problem_data &data, double uPrevPrev, double uPrev, double u, double uNext, double uNextNext);
}



#endif // MUSCL_H
