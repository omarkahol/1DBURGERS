#if !defined(PROBLEM_DATA_H)
#define PROBLEM_DATA_H

#include <iostream>
#include <vector>

namespace PDE::IO {
    struct problem_data {
        int nx;
        int nt;
        double t_final;
        std::string method;
        std::string scheme;
        std::vector<double> mesh;
        std::vector<double> u0;
    };
}

#endif // PROBLEM_DATA_H
