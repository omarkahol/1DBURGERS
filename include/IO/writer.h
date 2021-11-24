#if !defined(WRITER_H)
#define WRITER_H

#include <fstream>
#include <vector>

namespace PDE::IO {
    void writer(const char *fileName, const std::vector<std::vector<double>> &solution);
}

#endif // WRITER_H
