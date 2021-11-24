from scipy.integrate import quad
import numpy as np


file = open("config.1db", 'w')

file.write("% ----------------------------------------------------------------------------\n")
file.write("% ------------------------------ Config.1db file ----------------------------- \n")
file.write("% ----------------------------- CFD GROUP PROJECT----------------------------- \n")
file.write("% ----------------------------------------------------------------------------\n")
file.write("\n")

# Variables
Nt = 500
FinalTime = 2.0
Method = "EXPLICIT" #can select either EXPLICT or IMPLICIT
Flux = "GODUNOV" #can select either UPWIND or GODUNOV
LWCorrection = "TRUE" #activate or deactivate 2nd order correction sceme
SlopeLimiter = "SUPERBEE" #choose MINMOD, VAN_LEER, SUPERBEE, MC, NONE 
Nx = 100
Length = 2
u0 = lambda x: 1+np.sin(np.pi*x) #ANALYTICAL EXPRESSION OF THE INITIAL CONDITION


file.write("TFINAL = {}\n".format(FinalTime))
file.write("\n")
file.write("NT = {}\n".format(Nt))
file.write("\n")
file.write("METHOD = {}\n".format(Method))
file.write("\n")
file.write("FLUX = {}\n".format(Flux))
file.write("\n")
file.write("LW_CORRECTION = {}\n".format(LWCorrection))
file.write("\n")
file.write("SLOPE_LIMITER = {}\n".format(SlopeLimiter))
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

    if (i != len(x) - 1):
        meshstr = meshstr + "; "


file.write(meshstr)

file.close()

