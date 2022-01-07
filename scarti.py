import numpy as np
from math import *
import matplotlib.pyplot as plt
from numpy import genfromtxt
from scipy.interpolate import *
from scipy.interpolate.fitpack import splev, splrep

Nx = np.array([50, 100, 500, 1000]) #NX TEST VALUES

h = [] #save the mesh size to study convergence
err = [] #save the error

for n in range(len(Nx)-1):

    #index n will denote the coarse mesh and index n+1 the fine one
    #the goal is the computation of |u(n+1) I(n,n+1)*u(n)| 
    #I(n,n+1) is the interpolator operator from coarse to fine that must have at least order two
    # we use a cubic spline of order 3

    #Get the results from the coarse mesh 
    data = genfromtxt('Results/Caso_3/solution_RK_2_GODUNOV_VAN_LEER_TRUE_MUSCL_LINEAR_{:}.csv'.format(Nx[n]),delimiter=',') #import
    u1 = data[:,0:-1] #select the solution
    u1 = u1[-1,:] #select the final time
    x = np.linspace(-1, 1, Nx[n]) #determine the boundary points
    x1 =  0.5*(x[0:-1]+x[1:]) #determine the mesh point

    #Get the results from the fine mesh
    data = genfromtxt('Results/Caso_3/solution_RK_2_GODUNOV_VAN_LEER_TRUE_MUSCL_LINEAR_{:}.csv'.format(Nx[n+1]),delimiter=',') #import
    u2 = data[:,0:-1] #read the solution
    u2 = u2[-1,:] #select the final time
    x = np.linspace(-1, 1, Nx[n+1]) #compute the boundary points
    x2 =  0.5*(x[0:-1]+x[1:]) #determine the mesh points
    h.append(2./(Nx[n+1]-1)) #save the finest value of h

    tck = splrep(x1,u1,s=2) #determine the spline coefficients for the first solution
    u1_int = splev(x2,tck) #evaluate the spline on the fine mesh

    err.append(np.linalg.norm(u2-u1_int)/Nx[n+1]) #save the error

h = np.array(h)
err = np.array(err)


# Setting the figure
fig = plt.figure(1)
ax = fig.add_subplot(111)
ax.set_title('example', fontsize=20) 
ax.set_xlabel('h', fontsize=20)
ax.set_ylabel('Error (Norm-2)', fontsize=20)
ax.loglog(h,err, 'k-')
normalize = err[0]/(h[0]**1.5)
ax.loglog(h,normalize*h**1.5, 'r-')
plt.legend(['Error RK_2','O(h^1.5)'])

plt.show()
