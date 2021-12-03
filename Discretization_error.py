import numpy as np
from math import *
import matplotlib.pyplot as plt
from numpy import genfromtxt
from matplotlib.animation import FuncAnimation


Nx = np.array([500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700])
h = 2/(Nx-1)

TimeIdx = -2

err_vec1 = np.zeros((len(Nx,)))
err_vec2 = np.zeros((len(Nx,)))

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

for n in range(len(Nx)):
    data = genfromtxt('Results/solution_RK_3_GODUNOV_VAN_ALBADA_TRUE_MUSCL_PARABOLIC_{:}.csv'.format(Nx[n]),delimiter=',')
    u= data[:,0:-1]
    time = data[TimeIdx,-1]

    Analytic_sol = np.zeros((u.shape[1],))

    xAxis = np.linspace(-1,1,u.shape[1] + 1)
    meshPoints = 0.5*(xAxis[0:-1]+xAxis[1:])
    for i in range(len(meshPoints)):
        Analytic_sol[i] = u_exact(meshPoints[i], time)

    err_vec2[n] = np.linalg.norm(u[TimeIdx,:] - Analytic_sol)/Nx[n]
    err_vec1[n] = np.linalg.norm(u[TimeIdx,:] - Analytic_sol, 1)/Nx[n]
    

# Setting the figure
fig = plt.figure(1)
ax = fig.add_subplot(111)
ax.set_title('Error decay with h', fontsize=20) 
ax.set_xlabel('h', fontsize=20)
ax.set_ylabel('Error (Norm-1)', fontsize=20)
ax.loglog(h, err_vec1, 'r-')
ax.loglog(h, h, 'b-')
ax.loglog(h, h**2, 'k-')
#ax.plot(Nx, err_vec, 'r-')
plt.legend(['Norm-1', 'O(h)', 'O(h^2)'])

# Setting the figure
fig = plt.figure(2)
ax = fig.add_subplot(111)
ax.set_title('Error decay with h', fontsize=20) 
ax.set_xlabel('h', fontsize=20)
ax.set_ylabel('Error (Norm-2)', fontsize=20)
ax.loglog(h, err_vec2, 'r-')
ax.loglog(h, h, 'b-')
ax.loglog(h, h**2, 'k-')
plt.legend(['Norm-2', 'O(h)', 'O(h^2)'])
#ax.plot(Nx, err_vec, 'r-')

plt.show()

