#if !defined(PROBLEM_DATA_H)
#define PROBLEM_DATA_H

#include <iostream>
#include <vector>

namespace PDE::IO {
    struct problem_data {
        int nx;
        double CFL;
        double t_final;
        void (*method)(std::vector<double>*, std::vector<double>*, PDE::IO::problem_data&);
        double (*riemann_solver)(double,double);
        bool MUSCL;
        std::vector<double> mesh;
        std::vector<double> u0;
        std::string solution_filename;
    };
}

#endif // PROBLEM_DATA_H
