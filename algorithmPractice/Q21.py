import copy

def find_parent(parent, index):
    if parent[index[0]][index[1]] != index:
        parent[index[0]][index[1]] = find_parent(parent, parent[index[0]][index[1]])
    return parent[index[0]][index[1]]

def union_parent(parent, a, b):
    a = find_parent(parent, a)
    b = find_parent(parent, b)
    tmp = sorted([a, b])
    if tmp[0] == a:
        parent[b[0]][b[1]] = a
    else:
        parent[a[0]][a[1]] = b

def solve(map_arr):
    parent = [[] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            parent[i].append((i,j))
    a = False
    for now_i in range(n):
        for now_j in range(n):
            for x,y in zip(dx,dy):
                new_i = now_i+x
                new_j = now_j+y
                if new_i >= n or new_j >= n:
                    continue
                gap = abs(map_arr[now_i][now_j] - map_arr[new_i][new_j])
                if gap >= l and gap <= r:
                    union_parent(parent, [now_i, now_j], [new_i, new_j])
                    a = True
    result = [[[] for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            x,y = find_parent(parent, [i, j])
            result[x][y].append((i, j))
    for i in range(n):
        for j in range(n):
            count = len(result[i][j])
            if count <= 1:
                continue
            summary = sum([map_arr[x][y] for x, y in result[i][j]])
            answer = summary // count
            for x,y in result[i][j]:
                map_arr[x][y] = answer
    return a


dx = [0,1]
dy = [1,0]
q = []

n, l, r = map(int, input().split())
map_arr = []
for _ in range(n):
    map_arr.append(list(map(int, input().split())))

count = 0
while True:
    result = solve(map_arr)
    if not result:
        break
    count += 1

print(count)



