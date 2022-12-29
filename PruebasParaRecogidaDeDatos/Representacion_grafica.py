# -*- coding: utf-8 -*-
"""Untitled0.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/17HsYmAdbOJyzltowLk6wxwdIuhkBGvOh
"""
#Este código nos mostrará los gráficos de posición, abiadura, aceleración y posición en el plano XY
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

csv_file = "data.csv"
df = pd.read_csv(csv_file)
stuff = df.to_numpy()
t,ax,ay,az,gyx,gyy,gyz,mgx,mgy,mgz,pre=stuff.T
#print(t)

plt.xlabel("t [s]")
plt.ylabel("a [m/s^2]")

#Gráfico de aceleración
plt.plot(t,ax,label="ax")
plt.plot(t,ay,label="ay")
#plt.plot(t,az,label="az")
plt.grid()
plt.legend()
plt.show

dt = t[1] - t[0]
vx = [0]
vy = [0]
vz = [0]

for i in np.arange(len(t)-1):
  vx = vx + [vx[-1] + ax[i]*dt]
  vy = vy + [vy[-1] + ay[i]*dt]
  vz = vz + [vz[-1] + az[i]*dt]

#Gráfico de velocidad
plt.plot(t,vx, label="vx")
plt.plot(t,vy, label="vy")
#plt.plot(t,vz, label="vz")

plt.legend()
plt.grid()
plt.show()

dt = t[1] - t[0]
x = [0]
y = [0]
z = [0]

for i in np.arange(len(t)-1):
  x = x + [x[-1] + vx[i]*dt]
  y = y + [y[-1] + vy[i]*dt]
  z = z + [z[-1] + vz[i]*dt]

#Gráfico de posición
plt.plot(t,x, label="x")
plt.plot(t,y, label="y")
#plt.plot(t,z, label="z")

plt.legend()
plt.grid()
plt.show()

vx = [0]
vy = [0]

for i in np.arange(len(t)-1):
  vx = vx + [vx[-1] + ax[i]*dt]
  vy = vy + [vy[-1] + ay[i]*dt]
  vz = vz + [vz[-1] + az[i]*dt]

#Gráfico de posición en el plano XY
plt.plot(x,y)
plt.show()

