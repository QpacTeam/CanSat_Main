import matplotlib.pyplot as plt
import random
import time


class Function(object):
    def __init__(self, dimension, size=None):
        if size is None:
            size = [[0, 100], [0, 100], [0, 100]]

        self.fig = plt.figure()
        self.dimension = dimension
        if dimension == 3:
            self.ax = self.fig.add_subplot(projection="3d")

            self.ax.set_xlim3d(size[0][0], size[0][1])
            self.ax.set_ylim3d(size[1][0], size[1][1])
            self.ax.set_zlim3d(size[2][0], size[2][1])

            self.x = []
            self.y = []
            self.z = []

            self.plot = [self.x, self.y, self.z]

        else:
            self.ax = self.fig.add_subplot()
            self.ax.set_xlim(size[0][0], size[0][1])
            self.ax.set_ylim(size[1][0], size[1][1])

            self.x = []
            self.y = []

            self.plot = [self.x, self.y]

    def update(self, l):
        for i in range(self.dimension):
            self.plot[i].append(l[i])

    def draw(self, color):
        self.ax.plot(*self.plot, color=color)
        self.fig.canvas.draw()
        plt.pause(0.1)


if __name__ == "__main__":

    f1 = Function(3, [200, 200, 200])
    f2 = Function(2)
    f3 = Function(2)
    f4 = Function(2)

    x0 = 0
    y0 = 50
    z0 = 50

    for i in range(100):
        x = x0 + random.randint(1, 3) / 2
        y = y0 + random.randint(0, 1)
        z = 100 - i

        x0 = x
        y0 = y
        z0 = z

        f1.update([x, y, z])
        f2.update([x, z])
        f3.update([y, z])
        f4.update([x, y])

        f1.draw((0, 0, 1))
        f2.draw((1, 0, 0))
        f3.draw((0, 1, 0))
        f4.draw((1, 1, 0))

    plt.show()
