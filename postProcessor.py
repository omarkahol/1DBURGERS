import numpy as np
from math import *
import matplotlib.pyplot as plt
from numpy import genfromtxt
from matplotlib.animation import FuncAnimation

#   -------------------- CASES --------------------
#
#       './results/EXPLICIT_GODUNOV.csv'
#   './results/EXPLICIT_GODUNOV_2_ORD_SUPERBEE.csv'
#   './results/EXPLICIT_GODUNOV_2_ORD_VAN_LEER.csv'
#
#       './results/EXPLICIT_UPWIND.csv'
#   './results/EXPLICIT_UPWIND_2_ORD_SUPERBEE.csv
#   './results/EXPLICIT_UPWIND_2_ORD_VAN_LEER.csv'


data = genfromtxt('./results/EXPLICIT_GODUNOV.csv',delimiter=',')

fig = plt.figure()
ax = fig.add_subplot(111,xlim=(-1,1),ylim=(-3,3))
ax.set_title('solution')
ax.set_xlabel('x')
ax.set_ylabel('u(x,t)')
line, = ax.plot([],[],'k-',lw=2)
nTime, nPoints = data.shape
print(nTime, nPoints)
xAxis = np.linspace(-1,1,nPoints)

def animate(i):
    line.set_data(xAxis,data[i,:])

ani = FuncAnimation(fig, animate, frames=len(data[:,0]),interval=1)
plt.show()