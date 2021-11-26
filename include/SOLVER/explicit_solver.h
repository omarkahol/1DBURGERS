#if !defined(SOLVER_H)
#define SOLVER_H

#include <vector>
#include <iomanip>
#include "problem_data.h"
#include "fluxes.h"
#include "lw_correction.h"
#include "writer.h"

namespace PDE::SOLVER {
    void explicit_solver(std::vector<double> *solution, std::vector<double> *solutionPrev, PDE::IO::problem_data &data);
    double CFL(double u, double h, double k);
    double maximum(std::vector<double> *vec);
    double Twonorm(std::vector<double> *Vect);
}

#endif // SOLVER_H
