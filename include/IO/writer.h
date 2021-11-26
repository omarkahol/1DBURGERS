#if !defined(WRITER_H)
#define WRITER_H

#include <fstream>
#include <vector>


namespace PDE::IO {
    void writer(std::string fileName, const std::vector<double> *solution, std::ios_base::openmode value);
}

#endif // WRITER_H
