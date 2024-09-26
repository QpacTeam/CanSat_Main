import graph, antiparcer

antiparcer.init()

g1 = graph.Function(3, ([47, 48], [290, 310], [17, 18]))

#g1.update((47.5, 300, 17.5))

while True:
    l = antiparcer.get_data()
    if (l[0] > 47 and l[0] < 48 and l[1] > 290 and l[1] < 300 and l[2] > 17 and l[2] < 18):
        g1.update(l)
        g1.draw("b")