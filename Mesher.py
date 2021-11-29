from scipy.integrate import quad
import numpy as np
import math as mt

file = open("config.1db", 'w')

file.write("% ----------------------------------------------------------------------------\n")
file.write("% ------------------------------ Config.1db file ----------------------------- \n")
file.write("% ----------------------------- CFD GROUP PROJECT----------------------------- \n")
file.write("% ----------------------------------------------------------------------------\n")
file.write("\n")

# Variables

FinalTime = 3.0
Method = "RK_2" #can select either EXPLICT, RK_2, IMPLICIT
RiemannSolver = "GODUNOV" #can select either GODUNOV, ROE, ROE_FIX
MUSCL = "TRUE" #activate or deactivate 2nd order MUSCL scheme
Nx = 500
Length = 2
CFL_limit = 0.8
u0 = lambda x: -1.0*np.sign(x) if abs(x) < 0.5 else 0.0#ANALYTICAL EXPRESSION OF THE INITIAL CONDITION

filename = "solution.csv"

file.write("TFINAL = {}\n".format(FinalTime))
file.write("\n")
file.write("CFL = {}\n".format(CFL_limit))
file.write("\n")
file.write("METHOD = {}\n".format(Method))
file.write("\n")
file.write("RIEMANN_SOLVER = {}\n".format(RiemannSolver))
file.write("\n")
file.write("MUSCL = {}\n".format(MUSCL))
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

