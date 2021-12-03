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


data = genfromtxt('solution.csv',delimiter=',')


fig = plt.figure(1)
ax = fig.add_subplot(111, xlim=(-1,1), ylim=(0, data[-1,-1]))
time = data[:, -1]
u = data[:,:-1]
nTime, nPoints = u.shape
xAxis = np.linspace(-1, 1, nPoints+1)
meshPoints = 0.5*(xAxis[0:-1]+xAxis[1:])

# X-T plane -- Contour plot
X , T = np.meshgrid(xAxis, time)
ax.contourf(X, T, u)
ax.set_title('x-t plane')
ax.set_xlabel('x')
ax.set_ylabel('time')




skip = 20

x0 = meshPoints[0:-1:skip]

Characteristics = np.zeros((nTime, len(x0)-1))
index = np.arange(0,nPoints,skip)
Characteristics[0,:] = x0[0:-1]
s = 0.5*(u[:,0:-1]+u[:,1:])


for n in range(nTime-1):
    for i in range(0,len(index)-2):
        Characteristics[n+1,i] = Characteristics[n,i] + s[n,index[i]]*(time[n+1] - time[n])

ax.plot(Characteristics, time, 'k-', linewidth='1')
plt.show()
