RIGHT = 0
DOWN = 1
LEFT = 2
UP = 3


def createSpiralArray(array, n):
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


def getNbInversion(array):
    count = 0
    for i in range(len(array)):
        for j in range(i + 1, len(array)):
            if array[i] > array[j]:
                count += 1
    return count


def isSovable(array, size):
    isSolvable = False
    spiralArray = createSpiralArray(array, size)
    nbInversion = getNbInversion(spiralArray)
    if size % 2 and not nbInversion % 2:
        isSolvable = True
    # elif not size % 2:
    #
    #     #TODO verif si 0 est sur une ligne pair et nb inversion impair
    #     #TODO verif si 0 est une ligne impair et nb inversion est pair
    #     print("jtebez")
    # else:
    #     print("Not solvable")



    return isSolvable