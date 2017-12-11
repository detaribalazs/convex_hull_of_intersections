#!/usr/bin/python

if __name__ == "__main__":
    import matplotlib.pyplot as plt
    from operator import itemgetter
    from sys import argv

    lines = []
    points = []
    circles = []

    for filename in argv[1:]:
        pts = []
        for line in file(filename):
            data = line.split()
            if len(data) == 1:
                if pts:
                    points.append(pts)
                    pts = []
            elif len(data) == 2:
                pts.append(map(float, data))
            elif data[0] == 'L':
                lines.append(map(float, data[1:]))
            elif data[0] == 'C':
                circles.append(map(float, data[1:]))
        if pts:
            points.append(pts)

    fig = plt.gca()

    for x,y,r in circles:
        fig.add_patch(plt.Circle((x, y), radius=r, fill=False, ec='b'))

    for x1,y1,x2,y2 in lines:
        fig.add_line(plt.Line2D((x1, x2), (y1, y2), c='g', lw=1))

    pcolors  = ("ro", "rs", "ks", "kD")
    s = 0
    for pts in points:
        fig.plot(map(itemgetter(0), pts), map(itemgetter(1), pts), pcolors[s])
        s = (s + 1) % len(pcolors)

    plt.grid(True)
    plt.axis('equal')
    plt.show()
