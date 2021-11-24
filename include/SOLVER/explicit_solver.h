#if !defined(SOLVER_H)
#define SOLVER_H

#include <vector>
#include "problem_data.h"
#include "fluxes.h"
#include "lw_correction.h"

namespace PDE::SOLVER {
    void explicit_solver(std::vector<std::vector<double>> &solution, const PDE::IO::problem_data &data);
    double CFL(double u, double h, double k);
}

#endif // SOLVER_H
