import numpy as np
from math import *
import matplotlib.pyplot as plt
from numpy import genfromtxt
from matplotlib.animation import FuncAnimation

data = genfromtxt('Results/solution_RK_2_GODUNOV_VAN_LEER_TRUE_LAX_WENDROFF_1000.csv',delimiter=',')
time = data[:, -1]
u = data[:,0:-1]
TimeIdx = -2
fig_num = 1

print(len(time))


# Setting the figure
fig = plt.figure(fig_num)
ax = fig.add_subplot(111)
ax.set_title('Solution at time: t = {:f}'.format(time[TimeIdx]), fontsize=20) 
ax.set_xlabel('x', fontsize=20)
ax.set_ylabel('u(x,t)', fontsize=20)


# Plot of the solution obtained NUMERICALLY

nTime, nPoints = u.shape
xAxis = np.linspace(-1,1,nPoints + 1)
meshPoints = 0.5*(xAxis[0:-1]+xAxis[1:])

ax.plot(meshPoints, u[TimeIdx,:],'k*-', lw=2)

# Plot of the solution obtained ANALITICALLY

def u1(x,t):

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

Analytic_sol = np.zeros((nPoints,))

for i in range(len(meshPoints)):
    Analytic_sol[i] = u1(meshPoints[i], time[TimeIdx])

ax.plot(meshPoints, Analytic_sol, 'r-', lw = 2)
fig_num += 1

plt.legend(['Numerical solution', 'Analitical solution'])




plt.show()
