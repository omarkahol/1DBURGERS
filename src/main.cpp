#include "parser.h"
#include "armadillo"
#include "writer.h"
#include "explicit_solver.h"

int main(int argc, char *argv[])
{
	std::cout << "Initializing Parser" << std::endl;
	PDE::IO::parser p("config.1db");
	p.parse();
	PDE::IO::problem_data &data = p.get();
	std::cout << "Data parsed!" << std::endl;

	arma::vec time = arma::linspace(0,data.t_final,data.nt);

	std::vector<std::vector<double>> solution = std::vector<std::vector<double>>(data.nt);

	PDE::SOLVER::explicit_solver(solution,data);

	PDE::IO::writer("solution.csv",solution);


	return 0;


	
}