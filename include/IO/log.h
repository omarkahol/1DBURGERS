#if !defined(LOG_H)
#define LOG_H

#include <iostream>
#include <iomanip>

namespace PDE::IO {
    void title();
    void log_explicit(int it, double t, double k, double max_sol);
}

#endif // LOG_H
