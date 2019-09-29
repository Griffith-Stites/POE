import matplotlib.pyplot as plt
# import numpy as np
# import pandas as pd
import pickle

objects = []
with open('data.txt', 'rb') as openfile:
    while True:
        try:
            objects.append(pickle.load(openfile))
        except EOFError:
            break

objects = objects[0]
# print(objects[0][1])

x = []
y = []

for i in range(len(objects)-1):
    x.append(objects[i][0])
    y.append(objects[i][1])

plt.scatter(x, y, c='b', alpha=0.5)
plt.title('2D ScatterPlot of our Letter')
plt.xlabel('x')
plt.ylabel('y')
plt.show()
