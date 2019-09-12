# #!/usr/bin/env python

# import sys
# import argparse
# import random

# def make_puzzle(s, solvable, iterations):
# 	def swap_empty(p):
# 		idx = p.index(0)
# 		poss = []
# 		if idx % s > 0:
# 			poss.append(idx - 1)
# 		if idx % s < s - 1:
# 			poss.append(idx + 1)
# 		if idx / s > 0 and idx - s >= 0:
# 			poss.append(idx - s)
# 		if idx / s < s - 1:
# 			poss.append(idx + s)
# 		swi = random.choice(poss)
# 		p[idx] = p[swi]
# 		p[swi] = 0
	
# 	p = make_goal(s)
# 	for i in range(iterations):
# 		swap_empty(p)
	
# 	if not solvable:
# 		if p[0] == 0 or p[1] == 0:
# 			p[-1], p[-2] = p[-2], p[-1]
# 		else:
# 			p[0], p[1] = p[1], p[0]

# 	return p

# def make_goal(s):
# 	ts = s*s
# 	puzzle = [-1 for i in range(ts)]
# 	cur = 1
# 	x = 0
# 	ix = 1
# 	y = 0
# 	iy = 0
# 	while True:
# 		puzzle[x + y*s] = cur
# 		if cur == 0:
# 			break
# 		cur += 1
# 		if x + ix == s or x + ix < 0 or (ix != 0 and puzzle[x + ix + y*s] != -1):
# 			iy = ix
# 			ix = 0
# 		elif y + iy == s or y + iy < 0 or (iy != 0 and puzzle[x + (y+iy)*s] != -1):
# 			ix = -iy
# 			iy = 0
# 		x += ix
# 		y += iy
# 		if cur == s*s:
# 			cur = 0

# 	return puzzle

# if __name__ == "__main__":
# 	parser = argparse.ArgumentParser()

# 	parser.add_argument("size", type=int, help="Size of the puzzle's side. Must be >3.")
# 	parser.add_argument("-s", "--solvable", action="store_true", default=False, help="Forces generation of a solvable puzzle. Overrides -u.")
# 	parser.add_argument("-u", "--unsolvable", action="store_true", default=False, help="Forces generation of an unsolvable puzzle")
# 	parser.add_argument("-i", "--iterations", type=int, default=10000, help="Number of passes")

# 	args = parser.parse_args()

# 	random.seed()

# 	if args.solvable and args.unsolvable:
# 		print("Can't be both solvable AND unsolvable, dummy !")
# 		sys.exit(1)

# 	if args.size < 3:
# 		print("Can't generate a puzzle with size lower than 2. It says so in the help. Dummy.")
# 		sys.exit(1)

# 	if not args.solvable and not args.unsolvable:
# 		solv = random.choice([True, False])
# 	elif args.solvable:
# 		solv = True
# 	elif args.unsolvable:
# 		solv = False

# 	s = args.size

# 	puzzle = make_puzzle(s, solvable=solv, iterations=args.iterations)

# 	w = len(str(s*s))
# 	print("# This puzzle is %s" % ("solvable" if solv else "unsolvable"))
# 	print("%d" % s)
#     for y in range(s):
#         for x in range(s):
#             exit()


import sys
import random

##  function to find the number of digits of the max number of the puzzle
##  so we can apply a padding to all numbers and the final writing is smooth

def find_padding(max):
    i = 10
    res = 1
    while max / i >= 1:
        res += 1
        i *= 10
    return(res)

def createPuzzle(dim):
    tab = []
    for x in range(dim):
        tab += range(x * dim, (x+1) * dim)

    random.shuffle(tab)
    res = []
    for i in range(dim):
        res += [tab[i * dim: (i + 1) * dim]]
    return res

if __name__ == '__main__':
    if len(sys.argv) != 2:
        sys.stderr.write("usage generator.py [dimension taquin]\n")
        exit(1)
    try:
        dim = int(sys.argv[1])
        if dim >= 100 or dim <= 0:
            raise Exception("number should be between 1 and 99")
    except Exception as e:
        sys.stderr.write(str(e)+"\n")
        sys.stderr.write("usage generator.py x [dimension taquin (0 < x < 100)]\n")
        exit(1)

    ##  fill an array with the right number of elements depending on the puzzle dimension
    ##  asked from the user then write it on the random.txt file

    res = createPuzzle(dim)
    f = open('random.txt', "w+")
    padding = find_padding(dim * dim)
    f.write("## Randomly generated taquin of dimension "+ str(dim) +" ##\n")
    f.write(str(dim) + "\n")
    for x in range(dim):
        f.write(' '.join(str(e).ljust(padding) for e in res[x])+"\n")