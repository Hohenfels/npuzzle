import math


def manhattan(c1, c2):
    return abs(c1[0] - c2[0]) + abs(c1[1] - c2[1]) * 1.01


def euclidian(c1, c2):
    return math.sqrt((c1[0] - c2[0]) ** 2 + (c1[1] - c2[1]) ** 2)


def diagonal(c1, c2):
    return max(abs(c1[0] - c2[0]), abs(c1[1] - c2[1]))


def test(c1, c2):
    return int(c1[0] != c2[0] or c1[1] != c2[1])
