import matplotlib.pyplot as plt
import numpy as np


def DDA(x1, y1, x2, y2):
    dx = x2 - x1
    dy = y2 - y1
    steps = int(max(abs(dx), abs(dy)))
    xInc = dx / steps
    yInc = dy / steps
    x = x1
    y = y1
    X = []
    Y = []

    for i in range(steps + 1):
        X.append(round(x))
        Y.append(round(y))
        x += xInc
        y += yInc

    return X, Y


x1, y1 = map(int, input("Enter starting point: ").split())
x2, y2 = map(int, input("Enter ending point: ").split())

X, Y = DDA(x1, y1, x2, y2)

fig, ax = plt.subplots()
ax.plot(X, Y, color='red', linestyle='dotted')
plt.show()
