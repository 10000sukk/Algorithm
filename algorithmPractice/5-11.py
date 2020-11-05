from collections import deque

n,m = map(int, input().split())
array = []
for i in range(n):
    array.append(list(map(int,input())))

result = 0


directions = [(0,1),(0,-1),(1,0),(-1,0)]
def bfs(x,y):
    queue = deque([[x,y]])

    while queue:
        x,y = queue.popleft()
        for direction in directions:
            nx = x + direction[0]
            ny = y + direction[1]

            if nx < 0 or nx >= n or ny <0 or ny >= m:
                continue

            if array[nx][ny] == 1:
                array[nx][ny] = array[x][y] + 1
                queue.append([nx,ny])


bfs(0,0)
print(array[n-1][m-1])




