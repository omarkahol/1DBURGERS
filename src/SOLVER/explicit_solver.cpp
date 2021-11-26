#include "explicit_solver.h"

double PDE::SOLVER::CFL(double u, double h, double k) {
    return u*k/h;
}

double PDE::SOLVER::maximum(std::vector<double> *vec){
    double max = 0.;
    for (int i = 0; i < vec -> size(); i++){
        max = std::max(max,std::abs(vec->at(i)));
    }
    return max;
}

double PDE::SOLVER::Twonorm(std::vector<double> *Vect){
    double n = 0.;
    for (int i = 0; i < Vect->size(); i++){
        n += Vect->at(i)*Vect->at(i);
    }
    return sqrt(n);
}


void PDE::SOLVER::explicit_solver(std::vector<double> *solution, std::vector<double> *solutionPrev, PDE::IO::problem_data &data) {
    
    // CREATE A FUNCTION POINTER THAT POINTS TO THE CORRECT FLUX FUNCTION
    double (*flux)(double , double );
    if (data.flux == "UPWIND") {
        flux = &PDE::SOLVER::flux_upwind;
    } else if (data.flux=="GODUNOV") {
        flux = &PDE::SOLVER::flux_godunov;
    }

    //CREATE A FUNCTION POINTER THAT POINTS TO THE CORRECT FLUX FUNCTION
    double (*limiter)(double,double,double);
    if (data.slope_limiter == "VAN_LEER") {
        limiter = &PDE::SOLVER::van_leer;
    } else if (data.slope_limiter == "NONE") {
        limiter = [](double,double,double){return 1.0;};
    } else if (data.slope_limiter == "SUPERBEE") {
        limiter = &PDE::SOLVER::superbee;
    }

    //INITIALIZE THE SOLUTION WITH THE INITIAL CONDITION
    solutionPrev = &(data.u0);
    double NORM = PDE::SOLVER::Twonorm(solutionPrev);

    PDE::IO::writer(data.Solution_filename, solutionPrev, std::ios::out);


    double max_sol = maximum(solutionPrev);

    //COMPUTE SOME ITERATION FIXED DATA
	double h = data.mesh[1]-data.mesh[0];
	double k = data.CFL*h/max_sol;
    double FL, FR;
    double CL, CR, CFL_local;
    int jPrevPrev,jPrev, jNext;
    double t = 0.0;
    int counter = 0;


    std::cout << std::setw(15) << std::setfill(' ') << "Iteration" << std::setw(18) << std::setfill(' ') << "Time" << std::setw(30) << std::setfill(' ') << "Time increment" << std::setw(22) << std::setfill(' ') << "|| u ||" << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------" << std::endl;
    std::cout << std::endl;



    for (t; t < data.t_final; t += k) {

        max_sol = 0.0;
		for (int j=0; j<data.nx; j++) { //ITERATE IN THE CENTERAL DOMAIN

            jPrev = (j==0)?data.nx-1:j-1; // PREVIOUS CELL INDEX
            jNext = (j==data.nx-1)?0:j+1; //NEXT CELL INDEX
            if (j==1) {
                jPrevPrev = data.nx-1;
            } else if (j==0) {
                jPrevPrev = data.nx -2;
            } else {
                jPrevPrev = j-2;
            }


			FL = flux( solutionPrev->at(jPrev), solutionPrev->at(j) ); //LEFT FLUX
			FR = flux(solutionPrev->at(j), solutionPrev->at(jNext)); //RIGHT FLUX
			solution->at(j) = solutionPrev->at(j) - (k/h)*(FR-FL);

            //COMPUTE THE 2ND ORDER CORRECTION WITH SLOPE LIMITER
            if (data.lw_correction == "TRUE") {
                CFL_local = PDE::SOLVER::CFL(solutionPrev->at(jPrev),h,k);
                CL = PDE::SOLVER::correction(solutionPrev->at(jPrev), solutionPrev->at(j), CFL_local);
                CL = CL * limiter(solutionPrev->at(jPrevPrev),solutionPrev->at(jPrev),solutionPrev->at(j));
                
                CFL_local = PDE::SOLVER::CFL(solutionPrev->at(j),h,k);
                CR = PDE::SOLVER::correction(solutionPrev->at(j),solutionPrev->at(jNext), CFL_local);
                CR = CR * limiter(solutionPrev->at(jPrev),solutionPrev->at(j),solutionPrev->at(jNext));

                solution->at(j) = solution->at(j) - (k/h)*(CR-CL);
            }

            max_sol = std::max(max_sol, std::abs(solution->at(j)));


		}

        double NORM = PDE::SOLVER::Twonorm(solution);

        std::cout << std::setw(10) << std::setfill(' ') << counter << std::setw(25) << std::setfill(' ') << t << std::setw(25) << std::setfill(' ') << k << std::setw(25) << std::setfill(' ') << NORM << std::endl;

        k = data.CFL*h/max_sol;

        PDE::IO::writer(data.Solution_filename, solution, std::ios::app);


        solutionPrev = solution;

        counter++;

	}

}