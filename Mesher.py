from typing import Final
from scipy.integrate import quad
import numpy as np
import math as mt
import pandas as pd

file = open("config.1db", 'w')

file.write("% ----------------------------------------------------------------------------\n")
file.write("% ------------------------------ Config.1db file ----------------------------- \n")
file.write("% ----------------------------- CFD GROUP PROJECT----------------------------- \n")
file.write("% ----------------------------------------------------------------------------\n")
file.write("\n")

# Variables

FinalTime = 1.
Method = "RK_3" #can select either EXPLICT, RK_2, RK_3
RiemannSolver = "GODUNOV" #can select either GODUNOV, ROE_FIX
Limiter = "VAN_ALBADA" #can select among MINMOD, SUPERBEE, VAN_LEER, VAN_ALBADA, NONE
SECOND_ORDER_CORRECTION = "TRUE" #activate or deactivate 2nd order MUSCL scheme. Choice: TRUE or FALSE  //SECOND ORDER CORRECTION
SECOND_ORDER_CORRECTION_TYPE = "MUSCL_PARABOLIC" #if MUSCL == FALSE, it is considered. It can be selected among MUSCL_LINEAR, MUSCL_PARABOLIC, LAX_WENDROFF, KT
Nx = 1700
Length = 2
CFL = 0.4
u0 = lambda x: 1.0 if abs(x) < 0.5 else 0.0  #ANALYTICAL EXPRESSION OF THE INITIAL CONDITION ----> RK_3, VAN_ALBADA, GODUNOV, MUSCL_() 
#u0 = lambda x: np.piecewise(x, [abs(x) > 0.5, ((x >= -0.5)  and x <= 0), ((x <=0.5)  and x > 0)], [0, 1, -1])



filename = "Results/solution_" + Method + "_" + RiemannSolver + "_" + Limiter + "_"+\
             SECOND_ORDER_CORRECTION + "_" + SECOND_ORDER_CORRECTION_TYPE + "_" + str(Nx) + ".csv"

file.write("TFINAL = {}\n".format(FinalTime))
file.write("\n")
file.write("CFL = {}\n".format(CFL))
file.write("\n")
file.write("METHOD = {}\n".format(Method))
file.write("\n")
file.write("RIEMANN_SOLVER = {}\n".format(RiemannSolver))
file.write("\n")
file.write("LIMITER = {}\n".format(Limiter))
file.write("\n")
file.write("SECOND_ORDER_CORRECTION = {}\n".format(SECOND_ORDER_CORRECTION))
file.write("\n")
file.write("SECOND_ORDER_CORRECTION_TYPE = {}\n".format(SECOND_ORDER_CORRECTION_TYPE))
file.write("\n")
file.write("FILENAME = {}\n".format(filename))
file.write("\n")
file.write("NX = {}\n".format(Nx))
file.write("\n")
file.write("MESH = ")

#MESH 
# 0-------0-------0-------0  ==> 0, these are the boundary points
# 0---*---0---*---0---*---0  ==> *, these are the center points 

x = np.linspace(-0.5*Length, 0.5*Length, Nx) #THESE ARE THE BOUNDARIES
h = Length/(Nx-1)


meshPoints = 0.5*(x[0:-1]+x[1:]) #THIS ARE THE CONTROL POINTS --> AVERAGE OF THE BOUNDARY POINTS
meshstr = ""

for i in range(len(x)-1):
    sol = quad(u0, x[i], x[i+1])[0]/h #INTEGRATE FROM FIRST BOUNDARY TO SECOND BOUNDARY
    if (abs(sol) < 1e-10):
        sol = 0.0
    meshstr = meshstr +"("+str(meshPoints[i])+","+str(sol)+")"

    if (i != len(x) - 2):
        meshstr = meshstr + "; "


file.write(meshstr)

file.close()


file2 = open("Logo.txt", 'w')

file2.write("//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//")
file2.write("\n")
file2.write("//                                     _____  ______  _____                                  //")
file2.write("\n")
file2.write("//                                    /  __ \ |  ___||  _  \                                 //")
file2.write("\n")
file2.write("//                                    | /  \/ | |_   | | | |                                 //")
file2.write("\n")
file2.write("//                                    | |     |  _|  | | | |                                 //")
file2.write("\n")
file2.write("//                                    | \__/\ | |    | |/ /                                  //")
file2.write("\n")
file2.write("//                                     \____/ \_|    |___/                                   //")
file2.write("\n")
file2.write("//                                                                                           //")
file2.write("\n")
file2.write("//                                                                                           //")
file2.write("\n")
file2.write("//                                                                                           //")
file2.write("\n")
file2.write("//                          ____________ _____   ___ _____ _____ _____                       //")
file2.write("\n")
file2.write("//                          | ___ \ ___ \  _  | |_  |  ___/  __ \_   _|                      //")
file2.write("\n")
file2.write("//                          | |_/ / |_/ / | | |   | | |__ | /  \/ | |                        //")
file2.write("\n")
file2.write("//                          |  __/|    /| | | |   | |  __|| |     | |                        //")
file2.write("\n")
file2.write("//                          | |   | |\ \| \_/ |\__/ / |___| \__/\ | |                        //")
file2.write("\n")
file2.write("//                          \_|   \_| \_|\___/\____/\____/ \____/ \_/                        //")
file2.write("\n")
file2.write("//                                                                                           //")
file2.write("\n")
file2.write("//                                                                                           //")
file2.write("\n")
file2.write("//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//")
file2.write("\n")
file2.write("\n-----------------------------------------------------------------------------------------------\n\n")
Names="{:<30}".format(" ") + "{:<35}".format("This project has been developed by:\n\n") +\
            "{:>40}".format("- ") + "{:<40}".format("Omar Kahol") + "{:>15}".format(" \n") +\
            "{:>40}".format("- ") + "{:<40}".format("Marta Pederzolli") + "{:>15}".format(" \n")+\
            "{:>40}".format("- ") + "{:<40}".format("Francesca Cerbone") + "{:>15}".format(" \n") +\
            "{:>40}".format("- ") + "{:<40}".format("Cosimo Capecchi") +"{:>15}".format(" ") 

file2.write(Names + "\n\n\n\n")

Text = "The 1-Dimensional Burgers' equation:\n\n"\
        "{:<30}".format(" ") + "{:^20}".format(" u_{t} + u*(u)_{x} = 0") + "{:>30}".format(" \n\n") +\
        "will be solved using the following configuration: \n" +\
        "------------------------------------------------------------------------------------------------\n" \
        "{:<28}".format("|   NUMBER OF VOLUMES") + "{:>4}".format(":") + "{:<12}".format(" ")+ "{:<35}".format(Nx) + "{:>18}".format("|\n") + \
        "{:<28}".format("|   VOLUME DIMENSION") + "{:>4}".format(":") + "{:<12}".format(" ") + "{:<35}".format(h) + "{:>18}".format("|\n") + \
        "{:<28}".format("|   COURANT NUMBER") + "{:>4}".format(":") + "{:<12}".format(" ") + "{:<35}".format(CFL) + "{:>18}".format("|\n") +\
            "{:<28}".format("|   FINAL TIME") + "{:>4}".format(":") + "{:<12}".format(" ") + "{:<35}".format(FinalTime) + "{:>18}".format("|\n") + \
                "{:<28}".format("|   TIME INTEGRATION") + "{:>4}".format(":") + "{:<12}".format(" ") + "{:<35}".format(Method) + "{:>18}".format("|\n") +\
                    "{:<28}".format("|   RIEMANN SOLVER") + "{:>4}".format(":") + "{:<12}".format(" ") + "{:<35}".format(RiemannSolver) + "{:>18}".format("|\n") +\
                        "{:<28}".format("|   SECOND ORDER CORRECTION") + "{:>4}".format(":") + "{:<12}".format(" ") + "{:<35}".format(SECOND_ORDER_CORRECTION) + "{:>18}".format("|\n") +\
                            "{:<28}".format("|   RECONSTRUCTION TYPE") + "{:>4}".format(":") + "{:<12}".format(" ") + "{:<35}".format(SECOND_ORDER_CORRECTION_TYPE) + "{:>18}".format("|\n") +\
                                "{:<28}".format("|   FLUX/SLOPE LIMITER") + "{:>4}".format(":") + "{:<12}".format(" ") + "{:<35}".format(Limiter) + "{:>18}".format("|\n") +\
                                 "------------------------------------------------------------------------------------------------\n\n" \



file2.write(Text)



file2.close()

