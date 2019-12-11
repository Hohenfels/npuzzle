import pygame

windowSize = 900
red = (255, 0, 0)

class Tile():
    def __init__(self, posX, posY, val):
        self.val = int(val)
        self.x = posX
        self.y = posY
        self.target = (self.x, self.y)
        self.isMoving = False

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return f"{self.val} x:{self.x} y:{self.y}"

    def moveTo(self, dir):
        self.target = (self.x + dir[0], self.y + dir[1])
        print(self, self.target, dir)

    def move(self, slidingSpeed):
        if self.x != self.target[0] or self.y != self.target[1]:
            self.isMoving = True
            self.x = self.x + (self.target[0] - self.x) / slidingSpeed if abs((self.target[0] - self.x) / slidingSpeed) > 0.05 else self.target[0]
            self.y = self.y + (self.target[1] - self.y) / slidingSpeed if abs((self.target[1] - self.y) / slidingSpeed) > 0.05 else self.target[1]
        else:
            self.isMoving = False

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

    def moving(state):
        for tile in state:
            if tile.isMoving:
                return True
        return False

    window = pygame.display.set_mode((windowSize + 250, windowSize))
    pygame.init()
    pygame.display.set_caption('N-Puzzle')
    done = False
    tileSize = windowSize / puzzleSize
    fontSize = 30 + (10 - size) * 10
    moveIdx = -1
    slidingSpeed = 30

    fontSideMenu = pygame.font.SysFont(None, 44)

    while not done:
        textSideMenu = fontSideMenu.render(f"Step: {moveIdx + 1} / {len(moves)}", True, red)
        window.fill((0, 0, 0))
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    done = True
                elif event.key == pygame.K_RIGHT:
                    if not moving(state) and moveIdx < len(moves):
                        moveIdx += 1
                        state[moves[moveIdx][0]].moveTo((moves[moveIdx][1][0] * tileSize, moves[moveIdx][1][1] * tileSize))
                elif event.key == pygame.K_LEFT:
                    if not moving(state) and moveIdx >= 0:
                        state[moves[moveIdx][0]].moveTo((-moves[moveIdx][1][0] * tileSize, -moves[moveIdx][1][1] * tileSize))
                        moveIdx -= 1
                elif event.key == pygame.K_PAGEUP:
                    slidingSpeed -= 5 if slidingSpeed - 5 > 0 else 0
                    print(f"Speeding up sliding speed: {slidingSpeed}")
                elif event.key == pygame.K_PAGEDOWN:
                    print(f"Slowing down sliding speed: {slidingSpeed}")
                    slidingSpeed += 5
        for tile in state:
            if tile.val != 0:
                tile.move(slidingSpeed)
                pygame.draw.rect(window, (255, 127, 80), pygame.Rect(tile.x, tile.y, tileSize - 2, tileSize - 2))
                window.blit(pygame.font.SysFont(None, 
                    fontSize, 1).render(str(tile.val),
                    False,(255, 255, 255)),
                    (tile.x + tileSize / 2 - len(str(tile.val)) * fontSize / 2,
                    tile.y + tileSize / 2 - len(str(tile.val)) * fontSize / 2))
            window.blit(textSideMenu, (windowSize + 10, 5))
        pygame.display.update()
    pygame.quit()

if __name__ == "__main__":
    initState, size, moves = parse('path.txt')
    visu(initState, moves, size)

"""
TODO: Side menu avec path length et legende des controles du visu
TODO: Plutot qu'espace faire left-right pour next-prev

"""