from collections import deque

n, k = map(int, input().split())
arr = []
for _ in range(n):
    arr.append(list(map(int, input().split())))

s, x, y = map(int, input().split())
x -= 1
y -= 1
dx = [0,0,1,-1]
dy = [1,-1,0,0]
q = deque()
tmp = []
for i in range(n):
    for j in range(n):
        if arr[i][j] != 0:
            tmp.append([arr[i][j], i, j])
tmp.sort(key=lambda x: x[0])
q.append(tmp)


time = 0
while q:
    time += 1
    if time > s or arr[x][y] != 0:
        break
    virus_arr = q.popleft()
    tmp = []
    for virus, r, c in virus_arr:
        for x1, y1 in zip(dx, dy):
            if r+x1 < 0 or r+x1 >= n or c+y1 < 0 or c+y1 >= n:
                continue
            if arr[r+x1][c+y1] == 0:
                arr[r+x1][c+y1] = virus
                tmp.append([virus, r+x1, c+y1])
    if len(tmp) != 0:
        tmp.sort(key=lambda x:x[0])
        q.append(tmp)

print(arr[x][y])