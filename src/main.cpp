#include "parser.h"
#include "armadillo"
#include "solver.h"
#include "Simulation_parser.h"
#include <chrono>
#include <thread>



int main(int argc, char *argv[])
{	
	std::system("clear");
	PDE::IO::Simulation_parser Sp("Logo.txt");
	Sp.Simulation_parse();
	Sp.Displayer();

	std::this_thread::sleep_for(std::chrono::seconds(2));
	
	std::cout << "Initializing Parser" << std::endl;
	PDE::IO::parser p("config.1db");
	p.parse();
	PDE::IO::problem_data data = p.get();
	std::cout << "Data parsed!" << std::endl;
	std::cout << "\n\n" << std::endl;

	std::vector<double> solutionPrev = std::vector<double> (data.nx);	//ALLOCATE MEMORY FOR PREVIOUS TIME-STEP SOLUTION
	std::vector<double> solution = std::vector<double> (data.nx);		//ALLOCATE MEMORY FOR CURRENT TIME-STEP SOLUTION

	PDE::IO::title();
	data.method(&solution, &solutionPrev, data);

	std::cout << "\n\nConvergence succeded!\n" << std::endl;
	std::cout << "Correct execution!" << std::endl;
	return 0;


	
}