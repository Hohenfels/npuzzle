from Classes.Node import Node
import numpy

def solvePuzzle(puzzle):

    #### TODO: Check if puzzle is solvable

    initialNode = Node(heuristics.manhattan, puzzle, size = 2147483647)
    bestNode = initialNode
    seen = [initialNode.hash]

    while not bestNode.solved:
        nodes = getNodeChildren(bestNode, seen)
        seen.extend([n.hash for n in nodes])

        if not nodes:
            print('Something wxent wrong, need to rollback')
            exit()

        scores = [n.score for n in nodes]
        bestNode = nodes[scores.index(min(scores))]

    return node

def getNodeChildren(parent, seen): ## parent is a Node
    l = []

    c = parent.getEmptyCoords()
    puzzle = []

    for move in [(0, 1), (0, -1), (-1, 0), (1, 0)]:


    return l
