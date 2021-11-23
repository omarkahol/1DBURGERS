#include "parser.h"
#include "metodi.h"
#include "armadillo"

int main(int argc, char *argv[])
{
	std::cout << "Initializing Parser" << std::endl;
	PDE::IO::parser p("config.1db");
	p.parse();
	PDE::IO::problem_data &data = p.get();
	std::cout << "Data parsed!" << std::endl;

	arma::vec time = arma::linspace(0,data.t_final,data.nt);
	double L = data.mesh[data.nx-1]-data.mesh[0];
	double h = L/(data.nx+1);
	double k = data.t_final/(data.nt+1);

	std::vector<std::vector<double>> solution = std::vector<std::vector<double>>(data.nt);
	
	for (int n=0; n<data.nt; n++) {
		if (n==0) {
			solution[n] = data.u0;
		} else {
			solution[n] = std::vector<double>(data.nx);

			for (int j=0; j<data.nx; j++) {

				double FL{0.0};
				double FR{0.0};

				if (j==0) { //periodic BC

					FL = PDE::SOLVER::flux_godunov(solution[n-1][data.nx-1], solution[n-1][j]);
					FR = PDE::SOLVER::flux_godunov(solution[n-1][j], solution[n-1][j+1]);

				} else if (j==data.nx-1) { //periodic BC

					FL = PDE::SOLVER::flux_godunov(solution[n-1][j-1], solution[n-1][j]);
					FR = PDE::SOLVER::flux_godunov(solution[n-1][j], solution[n-1][0]);

				} else { //internal domain
					FL = PDE::SOLVER::flux_godunov(solution[n-1][j-1], solution[n-1][j]);
					FR = PDE::SOLVER::flux_godunov(solution[n-1][j], solution[n-1][j+1]);
				}

				solution[n][j] = solution[n-1][j] - (k/h)*(FR-FL);
			}
		}
	}

	std::fstream f;

    f.open("solution.csv",std::ios::out);
    for(int t=0; t<data.nt; t++) {
      for(int i=0; i<data.nx; i++){
        f << solution[t][i];
        if (i != data.nx-1){
          f << ",";
        }
      }
      f<<std::endl;
    }
    f.close();

	return 0;


	
}