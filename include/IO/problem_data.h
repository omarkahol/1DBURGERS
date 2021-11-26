#if !defined(PROBLEM_DATA_H)
#define PROBLEM_DATA_H

#include <iostream>
#include <vector>

namespace PDE::IO {
    struct problem_data {
        int nx;
        double CFL;
        double t_final;
        std::string method;
        std::string flux;
        std::string lw_correction;
        std::vector<double> mesh;
        std::vector<double> u0;
        std::string slope_limiter;
        std::string Solution_filename;
    };
}

#endif // PROBLEM_DATA_H
