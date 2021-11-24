#include "writer.h"

void PDE::IO::writer(const char *fileName, const std::vector<std::vector<double>> &solution) {
    std::fstream f;

    int nt = solution.size();
    int nx = solution[0].size();

    f.open(fileName,std::ios::out);

    for(int t=0; t<nt; t++) {
      for(int i=0; i<nx; i++){
        f << solution[t][i];
        if (i != nx-1){
          f << ",";
        }
      }
      f<<std::endl;
    }
    f.close();
}