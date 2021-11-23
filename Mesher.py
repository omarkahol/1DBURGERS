from scipy.integrate import quad
import numpy as np


file = open("config.1db", 'w')


file.write("% ----------------------------------------------------------------------------\n")
file.write("% ------------------------------ Config.1db file ----------------------------- \n")
file.write("% ----------------------------- CFD GROUP PROJECT----------------------------- \n")
file.write("% ----------------------------------------------------------------------------\n")
file.write("\n")

# Variables

Nt = 1000
FinalTime = 1.0
Method = "EXPLICIT"
Scheme = "UPWIND"
Nx = 500
h = 2.0/(Nx+1)


file.write("TFINAL = {}\n".format(FinalTime))
file.write("\n")
file.write("NT = {}\n".format(Nt))
file.write("\n")
file.write("METHOD = {}\n".format(Method))
file.write("\n")
file.write("SCHEME = {}\n".format(Scheme))
file.write("\n")
file.write("NX = {}\n".format(Nx))
file.write("\n")
#file.write("K = {}\n".format(k))
#file.write("\n")
#file.write("H = {}\n".format(h))
#file.write("\n")

file.write("MESH = ")


IniSol = lambda xx: -np.sin(np.pi*xx)

x = np.linspace(-1, 1, Nx)
meshstr = ""

for i in range(len(x)):

    sol = quad(IniSol, x[i] - 0.5*h, x[i] + 0.5*h)[0]/h
    if (abs(sol) < 1e-10):
        sol = 0.0
    meshstr = meshstr +"("+str(x[i])+","+str(sol)+")"

    if (i != len(x) - 1):
        meshstr = meshstr + "; "

    


file.write(meshstr)


file.close()

