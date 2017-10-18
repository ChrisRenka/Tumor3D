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

xn = []
yn = []
zn = []

fNecro = "Resultados\\{}\\necro{}.txt".format(nSim, nFrame)
with open(fNecro,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        xn.append(int(row[0]))
        yn.append(int(row[1]))
        zn.append(int(row[2]))

ax.scatter(xn, yn, zn, c = 'k', marker = 'o')

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
