from Classes.Node import Node
import heuristics as hr
import numpy as np

heuristics = {1: hr.manhattan, 2: hr.euclidian, 3: hr.diagonal}

def solvePuzzle(puzzle, size, heuristic):

    #### TODO: Check if puzzle is solvable

    initialNode = Node(heuristics.get(heuristic), puzzle, size = size)

    bestNode = initialNode
    seen = [initialNode.hash]

    while not bestNode.solved:
        nodes = getNodeChildren(bestNode, seen)
    
        if not nodes:
            bestNode = bestNode.parent
            # print('Something went wrong, need to rollback')
            # exit()
        else:
            scores = [n.score for n in nodes]
            
            # print("BestNode :", bestNode)
            # print("Children :", nodes)
            # print("Scores :", scores)
            
            
            bestNode = nodes[scores.index(min(scores))]
            seen.append(bestNode.hash)

    printPath(bestNode)
    return bestNode

def getNodeChildren(parent, seen): ## parent is a Node
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