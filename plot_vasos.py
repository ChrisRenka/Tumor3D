from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import csv

print ("Número da simulação:")
nSim = input()
print ("Número do frame:")
nFrame = input()

fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')

xs = []
ys = []
zs = []

fVasos = "Resultados\\{}\\vasos{}.txt".format(nSim, nFrame)
with open(fVasos,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        xs.append(int(row[0]))
        ys.append(int(row[1]))
        zs.append(int(row[2]))

ax.scatter(xs, ys, zs, c = 'r', marker = 'o')

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

plt.show()