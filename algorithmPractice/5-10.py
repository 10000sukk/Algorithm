from collections import deque

n,m = map(int, input().split())

array = []
for i in range(4):
    array.append(list(map(int,list(input()))))


directions = [(0,1), (0,-1), (1,0), (-1,0)]

result = 0


def bfs(x,y):
    queue = deque([[x,y]])
    array[x][y] = 1

    while queue:
        temp = queue.popleft()
        for direction in directions:
            nx = temp[0] + direction[0]
            ny = temp[1] + direction[1]

            if nx < 0 or nx >=4 or ny < 0  or ny >=5:
                continue

            if array[nx][ny] == 0:
                array[nx][ny] = 1
                queue.append([nx, ny])

for i in range(n):
    for j in range(m):
        if array[i][j] == 0:
            result += 1
            bfs(i,j)

print(result)
