from scipy.integrate import quad
import numpy as np


file = open("config.1db", 'w')

file.write("% ----------------------------------------------------------------------------\n")
file.write("% ------------------------------ Config.1db file ----------------------------- \n")
file.write("% ----------------------------- CFD GROUP PROJECT----------------------------- \n")
file.write("% ----------------------------------------------------------------------------\n")
file.write("\n")

# Variables

FinalTime = 1.3
Method = "EXPLICIT" #can select either EXPLICT or IMPLICIT
Flux = "UPWIND" #can select either UPWIND or GODUNOV
LWCorrection = "TRUE" #activate or deactivate 2nd order correction sceme
SlopeLimiter = "SUPERBEE" #choose MINMOD, VAN_LEER, SUPERBEE, MC, NONE 
Nx = 500
Length = 2
CFL_limit = 0.6
u0 = lambda x: -1.0 if x > -0.5 and x<0 else 1.0 if x>0 and x<0.5 else 0 #ANALYTICAL EXPRESSION OF THE INITIAL CONDITION

filename = Method + "_" + Flux 
if (LWCorrection == "TRUE"):
    filename += "_2_ORD_" + SlopeLimiter + ".csv"
else:
    filename += ".csv"

file.write("TFINAL = {}\n".format(FinalTime))
file.write("\n")
file.write("CFL = {}\n".format(CFL_limit))
file.write("\n")
file.write("METHOD = {}\n".format(Method))
file.write("\n")
file.write("FLUX = {}\n".format(Flux))
file.write("\n")
file.write("LW_CORRECTION = {}\n".format(LWCorrection))
file.write("\n")
file.write("SLOPE_LIMITER = {}\n".format(SlopeLimiter))
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

    if (i != len(x) - 1):
        meshstr = meshstr + "; "


file.write(meshstr)

file.close()

