import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

import pickle
# heatmap
objects = []
with open('lab2/data.txt', 'rb') as openfile:
    while True:
        try:
            objects.append(pickle.load(openfile))
        except EOFError:
            break
objects = objects[0]

x = []
y = []
z = []

for i in range(len(objects)-1):
    x.append(objects[i][0])
    y.append(objects[i][1])
    z.append(objects[i][2])

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.scatter(x, y, z, c='b', alpha=0.5)

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()
