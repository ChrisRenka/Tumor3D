from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import csv

print ("Número da simulação:")
nSim = input()
print ("Número do frame:")
nFrame = input()

fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')

xp = []
yp = []
zp = []

fProli = "Resultados\\{}\\proli{}.txt".format(nSim, nFrame)
with open(fProli,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        xp.append(int(row[0]))
        yp.append(int(row[1]))
        zp.append(int(row[2]))

ax.scatter(xp, yp, zp, c = 'b', marker = 'o')

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

plt.show()