import sys

arr = list(map(int, sys.stdin.readline().split()))

N = arr[0]
percentage =[arr[1]/100, arr[2]/100, arr[3]/100, arr[4]/100]
dirX = [1,-1,0,0]
dirY = [0,0,1,-1]

Map = [[0 for i in range(2*N +1)] for j in range(2*N + 1)]

prob = 0

def search(depth,x,y):
    if depth == N:
        return 1
    Map[x][y] = 1
    ret = 0
    for i in range(4):
        X = x + dirX[i]
        Y = y + dirY[i]

        if Map[X][Y]:
            continue
        ret += search(depth+1, X,Y)*percentage[i]

    Map[x][y] = 0
    return ret

print(search(0,N,N))



