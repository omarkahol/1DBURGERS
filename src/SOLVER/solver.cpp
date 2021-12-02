#include "solver.h"

double PDE::SOLVER::maximum(std::vector<double> *vec){
    double max = 0.;
    for (int i = 0; i < vec -> size(); i++){
        max = std::max(max,std::abs(vec->at(i)));
    }
    return max;
}

void PDE::SOLVER::explicit_solver(std::vector<double> *solution, std::vector<double> *solutionPrev, PDE::IO::problem_data &data) {

    //----------------------------------------------------------------------------------------------------------------------
    /*
    INITIALIZATION PART
        Copy the initial solution, write it in a file and find the maximum absolute value to compute the CFL.
        The control is not on the time step but on the CFL number
    */
    solutionPrev = &(data.u0);
    double t = 0.;
    PDE::IO::writer(data.solution_filename, solutionPrev, t, std::ios::out);
    double max_sol = maximum(solutionPrev);
    //----------------------------------------------------------------------------------------------------------------------
    
    //----------------------------------------------------------------------------------------------------------------------
    /*
    FIXED VARIABLES
        Compute some fixed variables.
            1) h ==> Mesh size
            2) k ==> Time step (from the user defined CFL number)
            3) flux_difference ==> the difference of the fluxes at the cell boundary
            4) jPrevPrev,jPrev, jNext ==> golbal DoF of neighbouring cells. They are computed in the
                framework of periodic BC
            5) iteration ==> current time iteration

    */
	double h = data.mesh[1]-data.mesh[0];
	double k = data.CFL*h/max_sol;
    double flux_difference;
    int jPrevPrev,jPrev, jNext, jNextNext;
    int iteration = 0;
    //--------------------------------------------------------------------------------------------------------------------------

    //START LOOPING IN TIME
    for (t; t < data.t_final; t += k) {

        max_sol = 0.0;
		for (int j=0; j<data.nx; j++) { //ITERATE IN THE CENTERAL DOMAIN
            
            
            jPrevPrev = (j==1)?(data.nx-1):(j==0)?(data.nx-2):j-2;
            jPrev = (j==0)?(data.nx-1):j-1; //J-1 CELL INDEX
            jNext = (j==data.nx-1)?0:j+1; //J+1 CELL INDEX
            jNextNext = (j==data.nx-2)?0:(j==data.nx-1)?1:j+1;
            

            //EVOLVE THE SOLUTION
            if (data.SEC_ORD_CORR) {
                flux_difference = data.Reconstruction(data, solutionPrev->at(jPrevPrev), solutionPrev->at(jPrev),
                    solutionPrev->at(j), solutionPrev->at(jNext),solutionPrev->at(jNextNext));
            } else {
                flux_difference = PDE::SOLVER::UPWIND(data,solutionPrev->at(jPrev), solutionPrev->at(j), solutionPrev->at(jNext));
            }

            solution->at(j) = solutionPrev->at(j) - (k/h)*flux_difference;
            max_sol = std::max(max_sol, std::abs(solution->at(j)));
		}

        k = data.CFL*h/max_sol;

        PDE::IO::writer(data.solution_filename, solution, t + k, std::ios::app);
        PDE::IO::log_explicit(iteration, t, k, max_sol);


        solutionPrev = solution;
        iteration++;

	}

}

void PDE::SOLVER::rk_solver(std::vector<double> *solution, std::vector<double> *solutionPrev, PDE::IO::problem_data &data) {
    
    //----------------------------------------------------------------------------------------------------------------------
    /*
    INITIALIZATION PART
        Copy the initial solution, write it in a file and find the maximum absolute value to compute the CFL.
        The control is not on the time step but on the CFL number
    */
    solutionPrev = &(data.u0);
    double t = 0.0;
    PDE::IO::writer(data.solution_filename, solutionPrev, t, std::ios::out);
    double max_sol = maximum(solutionPrev);
    //----------------------------------------------------------------------------------------------------------------------
    
    //----------------------------------------------------------------------------------------------------------------------
    /*
    FIXED VARIABLES
        Compute some fixed variables.
            1) h ==> Mesh size
            2) k ==> Time step (from the user defined CFL number)
            3) flux_difference ==> the difference of the fluxes at the cell boundary
            4) jPrevPrev,jPrev, jNext ==> golbal DoF of neighbouring cells. They are computed in the
                framework of periodic BC
            5) iteration ==> current time iteration

    */
	double h = data.mesh[1]-data.mesh[0];
	double k = data.CFL*h/max_sol;
    double flux_difference;
    int jPrevPrev,jPrev, jNext,jNextNext;
    int iteration = 0;
    //--------------------------------------------------------------------------------------------------------------------------

    std::vector<double> intSolution(data.nx);
    for (t; t < data.t_final; t += k) {

        max_sol = 0.0;

        //FIRST ITERATION
		for (int j=0; j<data.nx; j++) { //ITERATE IN THE CENTERAL DOMAIN

            jPrevPrev = (j==1)?(data.nx-1):(j==0)?(data.nx-2):j-2;
            jPrev = (j==0)?(data.nx-1):j-1; //J-1 CELL INDEX
            jNext = (j==data.nx-1)?0:j+1; //J+1 CELL INDEX
            jNextNext = (j==data.nx-2)?0:(j==data.nx-1)?1:j+2;


            //EVOLVE THE SOLUTION
            if (data.SEC_ORD_CORR) {
                flux_difference = data.Reconstruction(data, solutionPrev->at(jPrevPrev), solutionPrev->at(jPrev),
                    solutionPrev->at(j), solutionPrev->at(jNext),solutionPrev->at(jNextNext));
            } else {
                flux_difference = PDE::SOLVER::UPWIND(data, solutionPrev->at(jPrev), solutionPrev->at(j), solutionPrev->at(jNext));
            }

            intSolution[j] = solutionPrev->at(j) - 0.5*(k/h)*flux_difference;
		}

        //SECOND ITERATION
        for (int j=0; j<data.nx; j++) { //ITERATE IN THE CENTERAL DOMAIN

            jPrevPrev = (j==1)?(data.nx-1):(j==0)?(data.nx-2):j-2;
            jPrev = (j==0)?(data.nx-1):j-1; //J-1 CELL INDEX
            jNext = (j==data.nx-1)?0:j+1; //J+1 CELL INDEX
            jNextNext = (j==data.nx-2)?0:(j==data.nx-1)?1:j+2;

             //EVOLVE THE SOLUTION
            if (data.SEC_ORD_CORR) {
                flux_difference = data.Reconstruction(data, intSolution.at(jPrevPrev), intSolution.at(jPrev),
                    intSolution.at(j), intSolution.at(jNext),intSolution.at(jNextNext));
            } else {
                flux_difference = PDE::SOLVER::UPWIND(data, solutionPrev->at(jPrev), solutionPrev->at(j), solutionPrev->at(jNext));
            }
            

            solution->at(j) = intSolution[j] - (k/h)*flux_difference;
            max_sol = std::max(max_sol, std::abs(solution->at(j)));
		}

        k = data.CFL*h/max_sol;

        PDE::IO::writer(data.solution_filename, solution, t + k, std::ios::app);
        PDE::IO::log_explicit(iteration, t, k, max_sol);

        solutionPrev = solution;
        iteration++;
	}

}



void PDE::SOLVER::rk_4(std::vector<double> *solution, std::vector<double> *solutionPrev, PDE::IO::problem_data &data) {
    
    //----------------------------------------------------------------------------------------------------------------------
    /*
    INITIALIZATION PART
        Copy the initial solution, write it in a file and find the maximum absolute value to compute the CFL.
        The control is not on the time step but on the CFL number
    */
    solutionPrev = &(data.u0);
    double t = 0.0;
    PDE::IO::writer(data.solution_filename, solutionPrev, t, std::ios::out);
    double max_sol = maximum(solutionPrev);
    //----------------------------------------------------------------------------------------------------------------------
    
    //----------------------------------------------------------------------------------------------------------------------
    /*
    FIXED VARIABLES
        Compute some fixed variables.
            1) h ==> Mesh size
            2) k ==> Time step (from the user defined CFL number)
            3) flux_difference ==> the difference of the fluxes at the cell boundary
            4) jPrevPrev,jPrev, jNext ==> golbal DoF of neighbouring cells. They are computed in the
                framework of periodic BC
            5) iteration ==> current time iteration

    */
	double h = data.mesh[1]-data.mesh[0];
	double k = data.CFL*h/max_sol;
    double flux_difference;
    int jPrevPrev,jPrev, jNext,jNextNext;
    int iteration = 0;
    //--------------------------------------------------------------------------------------------------------------------------

    std::vector<double> intSolution(data.nx);
    for (t; t < data.t_final; t += k) {

        max_sol = 0.0;
        double k1, k2, k3;

        //FIRST ITERATION
		for (int j=0; j<data.nx; j++) { //ITERATE IN THE CENTERAL DOMAIN

            jPrevPrev = (j==1)?(data.nx-1):(j==0)?(data.nx-2):j-2;
            jPrev = (j==0)?(data.nx-1):j-1; //J-1 CELL INDEX
            jNext = (j==data.nx-1)?0:j+1; //J+1 CELL INDEX
            jNextNext = (j==data.nx-2)?0:(j==data.nx-1)?1:j+2;

            
            //EVOLVE THE SOLUTION FIRST TIME
            if (data.SEC_ORD_CORR) {
                flux_difference = data.Reconstruction(data, solutionPrev->at(jPrevPrev), solutionPrev->at(jPrev),
                    solutionPrev->at(j), solutionPrev->at(jNext),solutionPrev->at(jNextNext));
            } else {
                flux_difference = PDE::SOLVER::UPWIND(data, solutionPrev->at(jPrev), solutionPrev->at(j), solutionPrev->at(jNext));
            }

            k1 = k*flux_difference;

            //EVOLVE THE SOLUTION SECOND TIME
            if (data.SEC_ORD_CORR) {
                flux_difference = data.Reconstruction(data, solutionPrev->at(jPrevPrev) + 0.5*k1, solutionPrev->at(jPrev) + 0.5*k1,
                    solutionPrev->at(j) + 0.5*k1, solutionPrev->at(jNext) + 0.5*k1,solutionPrev->at(jNextNext) + 0.5*k1);
            } else {
                flux_difference = PDE::SOLVER::UPWIND(data, solutionPrev->at(jPrev) + 0.5*k1, solutionPrev->at(j) + 0.5*k1, solutionPrev->at(jNext) + 0.5*k1);
            }

            k2 = k*flux_difference;

            //EVOLVE THE SOLUTION THIRD TIME
            if (data.SEC_ORD_CORR) {
                flux_difference = data.Reconstruction(data, solutionPrev->at(jPrevPrev) + 2*k2 - k1, solutionPrev->at(jPrev) + 2*k2 - k1,
                    solutionPrev->at(j) + 2*k2 - k1, solutionPrev->at(jNext) + 2*k2 - k1,solutionPrev->at(jNextNext) + 2*k2 - k1);
            } else {
                flux_difference = PDE::SOLVER::UPWIND(data, solutionPrev->at(jPrev) + 2*k2 - k1, solutionPrev->at(j) + 2*k2 - k1, solutionPrev->at(jNext) + 2*k2 - k1);
            }

            k2 = k*flux_difference;

            solution->at(j) = solutionPrev->at(j) - 1./(6.*h)*(k1 + 4.*k2 + k3);

            max_sol = std::max(max_sol, std::abs(solution->at(j)));
		}

        k = data.CFL*h/max_sol;

        PDE::IO::writer(data.solution_filename, solution, t + k, std::ios::app);
        PDE::IO::log_explicit(iteration, t, k, max_sol);

        solutionPrev = solution;
        iteration++;
	}

}