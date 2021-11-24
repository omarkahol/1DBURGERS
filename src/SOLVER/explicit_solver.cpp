#include "explicit_solver.h"

double PDE::SOLVER::CFL(double u, double h, double k) {
    return std::abs(u)*k/h;
}

void PDE::SOLVER::explicit_solver(std::vector<std::vector<double>> &solution, const PDE::IO::problem_data &data) {
    
    // CREATE A FUNCTION POINTER THAT POINTS TO THE CORRECT FLUX FUNCTION
    double (*flux)(double,double);
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
    solution[0] = data.u0;

    //COMPUTE SOME ITERATION FIXED DATA
	double h = data.mesh[1]-data.mesh[0];
	double k = data.t_final/(data.nt+1);
    double FL, FR;
    double CL, CR, CFL;
    int jPrevPrev,jPrev, jNext;


    for (int n=1; n<data.nt; n++) {

		solution[n] = std::vector<double>(data.nx); //ALLOCATE MEMORY

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


			FL = flux(solution[n-1][jPrev], solution[n-1][j]); //LEFT FLUX
			FR = flux(solution[n-1][j], solution[n-1][jNext]); //RIGHT FLUX
			solution[n][j] = solution[n-1][j] - (k/h)*(FR-FL);

            //COMPUTE THE 2ND ORDER CORRECTION WITH SLOPE LIMITER
            if (data.lw_correction == "TRUE") {
                CFL = PDE::SOLVER::CFL(solution[n-1][jPrev],h,k);
                CL = PDE::SOLVER::correction(solution[n-1][jPrev], solution[n-1][j], CFL);
                CL = CL * limiter(solution[n-1][jPrevPrev],solution[n-1][jPrev],solution[n-1][j]);
                
                CFL = PDE::SOLVER::CFL(solution[n-1][j],h,k);
                CR = PDE::SOLVER::correction(solution[n-1][j],solution[n-1][jNext], CFL);
                CR = CR * limiter(solution[n-1][jPrev],solution[n-1][j],solution[n-1][jNext]);

                solution[n][j] = solution[n][j] - (k/h)*(CR-CL);
            }
		}
	}

}