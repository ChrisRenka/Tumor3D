from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import csv

print ("Número da simulação:")
nSim = input()
print ("Número do frame:")
nFrame = input()

fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')

xq = []
yq = []
zq = []

fQuie = "Resultados\\{}\\quie{}.txt".format(nSim, nFrame)
with open(fQuie,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        xq.append(int(row[0]))
        yq.append(int(row[1]))
        zq.append(int(row[2]))

ax.scatter(xq, yq, zq, c = 'y', marker = 'o')

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

plt.show()