import numpy as np
from heapq import heapify, heappush, heappop
from classes.Node import Node
from modules.Heuristics import *

heuristics = {1: manhattan, 2: euclidian}


def solvePuzzle(grid, size, target, heuristic):
    i = 0
    node = Node(heuristics.get(heuristic), grid, size=size)
    node = (node.score, node)
    stateTree = [node]
    seen = {node[1].hash}
    heapify(stateTree)

    while not str(node[1].state.ravel()) == str(target.ravel()):
        i += 1
        node = heappop(stateTree)
        print(node[1].state)
        for child in getChildren(node[1], seen):
            heappush(stateTree, (child.score, child))
            seen.add(child.hash)


def getChildren(parent, seen):
    c = parent.getEmptyCoords()
    newChildren = []
    for move in [(0, 1), (0, -1), (-1, 0), (1, 0)]:
        newCoords = (c[0] + move[0], c[1] + move[1])

        if newCoords[0] < 0 or newCoords[0] == parent.size or newCoords[1] < 0 or newCoords[1] == parent.size:
            continue

        newChild = Node(parent.hFunc, np.copy(parent.state), parent)

        newChild.state[c[1]][c[0]], newChild.state[newCoords[1]][newCoords[0]] = \
            newChild.state[newCoords[1]][newCoords[0]], newChild.state[c[1]][c[0]]

        if newChild.hash not in seen:
            newChildren.append(newChild)
    return newChildren


def printPath(node):
    it = 0
    n = []

    while node:
        it += 1
        n.append(node)
        node = node.parent

    for ni in n[::-1]:
        print(ni, "\n")
