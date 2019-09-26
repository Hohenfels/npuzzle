from Classes.Node import Node
import heuristics as hr

import numpy as np
from collections import deque
import timeit


heuristics = {1: hr.manhattan, 2: hr.euclidian, 3: hr.diagonal, 4: hr.test}

def solvePuzzle(puzzle, size, heuristic):

    #### TODO: Check if puzzle is solvable

    node = Node(heuristics.get(heuristic), puzzle, size = size)

    seen = set([node.hash])
    queue = set([node])
    i = 0

    while not node.solved:
        i += 1
        # queue = deque(list(sorted(queue, key = lambda n: n.score)))
        # # print([n.score for n in queue])
        node = min(queue, key = lambda n: n.score)
        queue.remove(node)
        
        for n in getNodeChildren(node, seen, queue):
            seen.add(n.hash)
            queue.add(n)



        #### DEBUG ####  
        # print("node :", node)
        # print("Children :", children)
        # print("Scores :", scores)

    printPath(node)
    print("real it",i)
    return node

def getNodeChildren(parent, seen, q): ## parent is a Node
    c = parent.getEmptyCoords()
    newChildren = []

    for move in [(0, 1), (0, -1), (-1, 0), (1, 0)]:
        newCoords = (c[0] + move[0], c[1] + move[1])
        if newCoords[0] < 0 or newCoords[0] == parent.size or newCoords[1] < 0 or newCoords[1] == parent.size: ## out of bounds
            continue
        newChild = Node(parent.hFunc, np.copy(parent.puzzle), parent)
        
        tmp = newChild.puzzle[c[1]][c[0]]
        newChild.puzzle[c[1]][c[0]] = newChild.puzzle[newCoords[1]][newCoords[0]]
        newChild.puzzle[newCoords[1]][newCoords[0]] = tmp

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
    print("iterations: ", it)