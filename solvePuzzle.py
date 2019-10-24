import numpy as np
from copy import deepcopy
from heapq import heapify, heappush, heappop
from checkSolvability import checkSolvability
from classes.Node import Node
from modules.Heuristics import *
from modules.ParsingErrors import SolvabilityError

heuristics = {1: manhattan, 2: euclidian}
directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]


def solvePuzzle(grid, size, target, heuristic):
    i = 0
    node = Node(heuristics.get(heuristic), grid, size=size)
    if not checkSolvability(node, size):
        raise(SolvabilityError())
    exit()
    node = (node.score, node.g, node)
    stateTree = [node]
    seen = {node[2].hash}
    heapify(stateTree)

    while len(stateTree):
        i += 1
        node = heappop(stateTree)
        for child in getChildren(node[2], seen):
            heappush(stateTree, (child.score, child.g, child))
            seen.add(child.hash)

    #printPath(node)


def getChildren(parent, seen):
    c = parent.getEmptyCoords()
    newChildren = []
    for move in directions:
        newCoords = (c[0] + move[0], c[1] + move[1])

        if newCoords[0] < 0 or newCoords[0] == parent.size or newCoords[1] < 0 or newCoords[1] == parent.size:
            continue

        newChild = Node(parent.hFunc, np.copy(parent.state), parent)

        newChild.state[c[1]][c[0]], newChild.state[newCoords[1]][newCoords[0]] = \
            newChild.state[newCoords[1]][newCoords[0]], newChild.state[c[1]][c[0]]

        if newChild.hash not in seen:
            print(newChild.score)
            newChildren.append(newChild)
    return newChildren


def printPath(node):
    node = node[2]
    it = 0
    n = []

    while node:
        it += 1
        n.append(node)
        node = node.parent

    for ni in n[::-1]:
        print(ni, "\n")
