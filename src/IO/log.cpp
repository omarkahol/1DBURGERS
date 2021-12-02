#include "log.h"

void PDE::IO::title() {
    std::cout << std::setw(15) << std::setfill(' ') << "Iteration" << std::setw(18) << std::setfill(' ') << "Time" << std::setw(30) << std::setfill(' ') << "Time increment" << std::setw(22) << std::setfill(' ') << "|| u ||" << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
}

void PDE::IO::log_explicit(int it, double t, double k, double max_sol) {
    std::cout 
    << std::setw(10) << std::setfill(' ') << it 
    << std::setw(25) << std::setfill(' ') << t 
    << std::setw(25) << std::setfill(' ') << k 
    << std::setw(25) << std::setfill(' ') << max_sol 
    << std::endl;
}