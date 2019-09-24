RIGHT = 0
DOWN = 1
LEFT = 2
UP = 3

def isSovable(array, n):
    isSolvable = False
    t, b, l, r = 0, n - 1, 0, n - 1
    direction = 0
    while t <= b and l <= r:
        if direction is RIGHT:
            i = l
            while i <= r:
                print(array[t][i])
                i += 1
            t += 1
        if direction is DOWN:
            

    return isSolvable