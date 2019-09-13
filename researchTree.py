# import numpy
from heuristics import *
from Classes.Node import Node

heuristics = {1: manhattan}

def solvePuzzle(puzzle, size, heuristic):

    #### TODO: Check if puzzle is solvable

    initialNode = Node(heuristics.get(heuristic), puzzle, size = size)
    print(initialNode.hash)
    # bestNode = initialNode
    # seen = [initialNode.hash]
    #
    # while not bestNode.solved:
    #     nodes = getNodeChildren(bestNode, seen)
    #     seen.extend([n.hash for n in nodes])
    #
    #     if not nodes:
    #         print('Something went wrong, need to rollback')
    #         exit()
    #
    #     scores = [n.score for n in nodes]
    #     bestNode = nodes[scores.index(min(scores))]

    # return node

def getNodeChildren(parent, seen): ## parent is a Node
    l = []

    c = parent.getEmptyCoords()
    puzzle = []

    for move in [(0, 1), (0, -1), (-1, 0), (1, 0)]:
        print("caca")

    # return l
