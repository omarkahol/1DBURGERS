#if !defined(SOLVER_H)
#define SOLVER_H

#include <vector>
#include "problem_data.h"
#include "riemann.h"
#include "limiters.h"
#include "writer.h"
#include "log.h"
#include "muscl.h"

namespace PDE::SOLVER {
    void explicit_solver(std::vector<double> *solution, std::vector<double> *solutionPrev, PDE::IO::problem_data &data);
    void rk_solver(std::vector<double> *solution, std::vector<double> *solutionPrev, PDE::IO::problem_data &data);
    void rk_4(std::vector<double> *solution, std::vector<double> *solutionPrev, PDE::IO::problem_data &data);
    double maximum(std::vector<double> *vec);
}

#endif // SOLVER_H
