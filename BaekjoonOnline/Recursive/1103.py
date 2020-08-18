import sys

arr1 = list(map(int,sys.stdin.readline().split()))
row = arr1[0]
col = arr1[1]
map = []
for i in range(row):
    temp = list(input())
    map.append(temp)

visit = [[0 for i in range(col)] for j in range(row)]
dp = [[-1 for i in range(col)] for j in range(row)]

result = []
def move(X, Y):

    if X < 0 or X >=row or Y < 0 or Y >= col:
        return 1
    if map[X][Y] == 'H':
        dp[X][Y] = 0
        return 1
    if dp[X][Y] != -1:
        return dp[X][Y]+1

    visit[X][Y] += 1
    if visit[X][Y] > 1:
        print(-1)
        sys.exit()



    num = int(map[X][Y])

    n = [0,0,0,0]
    n[0] = move(X-num,Y)
    n[1] = move(X+num,Y)
    n[2] = move(X,Y-num)
    n[3] = move(X,Y+num)

    max_n = 0
    for i in n:
        if max_n < i:
            max_n = i
    dp[X][Y] = max_n

    visit[X][Y] -= 1
    return dp[X][Y] + 1



move(0,0)
print(dp[0][0])

