import matplotlib.pyplot as plt
plt.title("DDA Algorithm")
plt.xlabel("x-axis")
plt.ylabel("y-axis")


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

x1 = int(input("Enter x1: "))
y1 = int(input("Enter y1: "))
x2 = int(input("Enter x2: "))
y2 = int(input("Enter y2: "))

X, Y = DDA(x1, y1, x2, y2)

plt.plot(X, Y)
plt.show()
