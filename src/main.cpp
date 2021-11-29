#include "parser.h"
#include "armadillo"
#include "solver.h"


int main(int argc, char *argv[])
{
	std::cout << "Initializing Parser" << std::endl;
	PDE::IO::parser p("config.1db");
	p.parse();
	PDE::IO::problem_data data = p.get();
	std::cout << "Data parsed!" << std::endl;
	std::cout << "\n" << std::endl;

	std::vector<double> solutionPrev = std::vector<double> (data.nx);	//ALLOCATE MEMORY FOR PREVIOUS TIME-STEP SOLUTION
	std::vector<double> solution = std::vector<double> (data.nx);		//ALLOCATE MEMORY FOR CURRENT TIME-STEP SOLUTION

	PDE::IO::title();
	data.method(&solution, &solutionPrev, data);
	return 0;


	
}