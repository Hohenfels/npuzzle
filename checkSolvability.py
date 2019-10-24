RIGHT = 0
DOWN = 1
LEFT = 2
UP = 3


def createOneDimPuzzle(array, n):
    t, b, l, r = 0, n - 1, 0, n - 1
    direction = RIGHT
    newArray = []
    while t <= b and l <= r:
        if direction is RIGHT:
            i = l
            while i <= r:
                newArray.append(array[t][i])
                i += 1
            t += 1
        elif direction is DOWN:
            i = t
            while i <= b:
                newArray.append(array[i][r])
                i += 1
            r -= 1
        elif direction is LEFT:
            i = r
            while i >= l:
                newArray.append(array[b][i])
                i -= 1
            b -= 1
        elif direction is UP:
            i = b
            while i >= t:
                newArray.append(array[i][l])
                i -= 1
            l += 1
        direction = (direction + 1) % 4
    return newArray


def findPosIntab(array, value):
    count = 0
    for i in array:
        if i == value:
            return count
        count += 1
    return count


def getPermuts(array):
    count = 0
    for i in range(len(array)):
        for j in range(i + 1, len(array)):
            if array[i] > 0 and 0 < array[j] < array[i]:
                count += 1
    return count


def checkSolvability(node, size):
    array = createOneDimPuzzle(node.state, size)
    nbPermut = getPermuts(array)
    if size % 2 != 0 and nbPermut % 2 == 0:
        return True
    else:
        coord = findPosIntab(array, 0)
        if nbPermut % 2 == 0 and coord % 2 or nbPermut % 2 and coord % 2 == 0:
            return True
    return False
