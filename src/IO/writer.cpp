#include <string>
#include "writer.h"

void PDE::IO::writer(std::string fileName, const std::vector<double> *solution, std::ios_base::openmode value) {
    std::fstream f;

    int nx = (*solution).size();
    
    f.open(fileName, value);

    for(int i=0; i<nx; i++){
      f << solution->at(i);
      if (i != nx-1){
        f << ",";
      }
    }
    f<<std::endl;
    
    f.close();
}