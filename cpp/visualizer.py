import pygame

windowSize = 900
rate = 60

class Tile():
    def __init__(self, posX, posY, val):
        self.val = int(val)
        self.x = posX
        self.y = posY

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return f"{self.val} x:{self.x} y:{self.y}"

    def move(self):
        pass

def parse(filename):
    
    def getZeroPos(state):
        if isinstance(state[0], Tile):
            state = [s.val for s in state]
        for i, v in enumerate(state):
            if v == 0:
                return i
        return -1

    def getDir(oldZero, newZero, size):
        if oldZero == newZero + 1:
            return (1, 0)
        elif oldZero == newZero - 1:
            return (-1, 0)
        elif oldZero == newZero + size:
            return (0, 1)
        elif oldZero == newZero - size:
            return (0, -1)
    
    initState = []
    moves = []
    size = 0
    currState = []
    lastZeroPos = -1

    with open(filename, 'r') as f:
        for line in f.readlines():
            if size == 0:
                size = len(line.split(' '))
            if len((initState)) != size * size:
                for l in line.split(' '):
                    initState.append(Tile(len(initState) % size * windowSize / size, len(initState) // size * windowSize / size, int(l)))
            else:
                if lastZeroPos == -1:
                    lastZeroPos = getZeroPos(initState)
                elif len(currState) == size * size:
                    newZeroPos = getZeroPos(currState)
                    moves.append((newZeroPos, getDir(lastZeroPos, newZeroPos, size)))
                    lastZeroPos = newZeroPos
                    currState = []
                else:
                    for l in line.split(' '):
                        currState.append(int(l))

    return initState, size, moves

def visu(state, moves, puzzleSize):
    window = pygame.display.set_mode((windowSize, windowSize))
    pygame.init()
    pygame.display.set_caption('N-Puzzle')
    done = False
    tileSize = windowSize / puzzleSize
    fontSize = 30 + (10 - size) * 10

    while not done:
        window.fill((0, 0, 0))
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    done = True
        for tile in state:
            if tile.val != 0:
                pygame.draw.rect(window, (255, 127, 80), pygame.Rect(tile.x, tile.y, tileSize - 2, tileSize - 2))
                window.blit(pygame.font.SysFont(None, fontSize, 1).render(str(tile.val), False, (255, 255, 255)), (tile.x + tileSize / 2 - len(str(tile.val)) / 2 * fontSize, tile.y + tileSize / 2 - len(str(tile.val)) / 2 * fontSize))
        pygame.display.update()

    pygame.quit()

if __name__ == "__main__":
    initState, size, moves = parse('path.txt')
    visu(initState, moves, size)