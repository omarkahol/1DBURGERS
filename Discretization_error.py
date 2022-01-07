import numpy as np
from math import *
import matplotlib.pyplot as plt
from numpy import genfromtxt
from matplotlib.animation import FuncAnimation
from scipy.integrate import quad

Nx = np.array([50, 100, 500])
Time_int = {0 : 'RK_2', 1 : 'EXPLICIT'}

TimeIdx = -1

err_vec1 = np.zeros((len(Nx)*len(Time_int),))
err_vec2 = np.zeros((len(Nx)*len(Time_int),))

# Definition of analitic solution 
def u_exact(x,t):

    t_star = 1.

    if (t <  t_star):

        if (x <= -0.5):
            return 0.
        elif  ((x > -0.5) and (x <=  -0.5 + t)):
            return (x + 0.5)/t
        elif ((x > -0.5 + t) and (x <= 0.5 + 0.5*t)):
            return 1.
        else:
            return 0.
    else:

        if (x <= -0.5):
            return 0.
        elif ((x > -0.5) and (x <= 1.5)):
            return x/t
        else:
            return 0.

    return

h = []
for k in range(len(Time_int)):
    for n in range(len(Nx)):
        data = genfromtxt('Results/Caso_3/solution_{:}_GODUNOV_VAN_LEER_TRUE_MUSCL_LINEAR_{:}.csv'.format(Time_int[k], Nx[n]),delimiter=',')
        u = data[:,0:-1]
        time = data[TimeIdx,-1]

        Analytic_sol = np.zeros((u.shape[1],))
        print(time)

        xAxis = np.linspace(-1,1,u.shape[1] + 1)
        meshPoints = 0.5*(xAxis[0:-1]+xAxis[1:])
        h.append(meshPoints[1]-meshPoints[0])
        for i in range(len(meshPoints)):
            Analytic_sol[i] = (1./h[n]) * quad(lambda x: u_exact(x, time), meshPoints[i]-0.5*h[n],meshPoints[i]+0.5*h[n])[0]

        err_vec2[n+k*len(Nx)] = np.linalg.norm(u[TimeIdx,:] - Analytic_sol, 2)/Nx[n]
    
    
h = np.array(h)
# Setting the figure
fig = plt.figure(1)
ax = fig.add_subplot(111)
ax.set_title('Linear approximation', fontsize=20) 
ax.set_xlabel('h', fontsize=20)
ax.set_ylabel('Error (Norm-2)', fontsize=20)
ax.loglog(h[0:len(Nx)], err_vec2[0:len(Nx)], 'k-')
ax.loglog(h[len(Nx):2*len(Nx)], err_vec2[len(Nx):2*len(Nx)], 'b-')
normalize1 = err_vec2[0]/(h[0]**1.5)
normalize2 = err_vec2[len(Nx)]/(h[0]**0.5)
ax.loglog(h,normalize1*h**1.5, 'r-')
ax.loglog(h,normalize2*h**0.5, 'g-')
plt.legend(['Error RK_2', 'Error  Expl', 'O(h^1.5)','O(h^0.5)'])

plt.show()




