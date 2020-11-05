from collections import deque
import copy
from itertools import combinations


def simulation(map_arr):
    arr = copy.deepcopy(map_arr)
    q = deque([])
    for i in range(n):
        for j in range(m):
            if arr[i][j] == 2:
                q.append((i, j))
    while q:
        r, c = q.popleft()
        for x, y in zip(dx, dy):
            if r + x >= n or r + x < 0 or c + y >= m or c + y < 0:
                continue

            if arr[r + x][c + y] != 0:
                continue

            arr[r + x][c + y] = 2
            q.append((r + x, c + y))

    result = 0
    for i in range(n):
        for j in range(m):
            if arr[i][j] == 0:
                result += 1
    return result


n, m = map(int, input().split())
map_arr = []
for _ in range(n):
    map_arr.append(list(map(int, input().split())))

dx = [0,0,1,-1]
dy = [1,-1,0,0]

safe_point = []
for i in range(n):
    for j in range(m):
        if map_arr[i][j] == 0:
            safe_point.append((i, j))

result = []
wall_case = list(combinations(safe_point, 3))
for wall in wall_case:
    for i,j in wall:
        map_arr[i][j] = 1
    result.append(simulation(map_arr))

    for i, j in wall:
        map_arr[i][j] = 0

print(max(result))




