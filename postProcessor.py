import numpy as np
from math import *
import matplotlib.pyplot as plt
from numpy import genfromtxt
from matplotlib.animation import FuncAnimation

#   ------------------------------ CASES ------------------------------
#
#       'Results/solution_RK_3_GODUNOV_VAN_ALBADA_TRUE_MUSCL_PARABOLIC_500.csv'
#   './results/EXPLICIT_GODUNOV_2_ORD_SUPERBEE.csv'
#   './results/EXPLICIT_GODUNOV_2_ORD_VAN_LEER.csv'
#
#       './results/EXPLICIT_UPWIND.csv'
#   './results/EXPLICIT_UPWIND_2_ORD_SUPERBEE.csv
#   './results/EXPLICIT_UPWIND_2_ORD_VAN_LEER.csv'


data = genfromtxt('Results/solution_RK_3_GODUNOV_VAN_ALBADA_TRUE_MUSCL_PARABOLIC_500.csv',delimiter=',')

fig = plt.figure(1)
ax = fig.add_subplot(111,xlim=(-1,1),ylim=(-3,3))
ax.set_title('Solution')
ax.set_xlabel('x')
ax.set_ylabel('u(x,t)')
line, = ax.plot([],[],'k-', lw=2)
nTime, nPoints = data.shape
time = np.array(data[:, -1])

nPoints = nPoints - 1
print(nTime, nPoints)
xAxis = np.linspace(-1,1,nPoints)

def animate(i):
    global line
    line.set_data(xAxis,data[i,0:-1])
    return line,

fixline, = ax.plot(np.zeros(2*nTime,),np.linspace(-3,3,2*nTime),'-k', lw=1)
ani = FuncAnimation(fig, animate, frames=len(data[:,0:-1]),interval=10,blit=True)
plt.show()


