import matplotlib.pyplot as plt
import random
from icecream import ic


class Function(object):
    def __init__(self, dimension, attributes: list, size=None, color=(0, 0, 1)):
        # if size is None:
        #     size = [[0, 100], [0, 100], [0, 100]]

        ic()

        self.fig = plt.figure()
        self.dimension = dimension
        self.attributes = attributes
        self.color = color

        if dimension == 3:
            ic()
            self.ax = self.fig.add_subplot(projection="3d")

            if size != None:
                self.ax.set_xlim3d(size[0][0], size[0][1])
                self.ax.set_ylim3d(size[1][0], size[1][1])
                self.ax.set_zlim3d(size[2][0], size[2][1])

            self.x = []
            self.y = []
            self.z = []

            self.plot = [self.x, self.y, self.z]

        else:
            ic()
            self.ax = self.fig.add_subplot()

            if size != None:
                self.ax.set_xlim(size[0][0], size[0][1])
                self.ax.set_ylim(size[1][0], size[1][1])

            self.x = []
            self.y = []

            self.plot = [self.x, self.y]

    def update(self, l):
        for i in range(self.dimension):
            self.plot[i].append(l[i])

    def draw(self, color=None):
        if color == None:
            color = self.color
        self.ax.plot(*self.plot, color=color)
        self.fig.canvas.draw()
        plt.pause(0.1)


def End():
    plt.show()


if __name__ == "__main__":

    f1 = Function(3, [[0, 200], [0, 200], [0, 200]])
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
