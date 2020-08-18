import sys
sys.setrecursionlimit(100000)

map_arr = []
map_size = []
while True:
    arr = list(map(int, input().split()))
    if arr[0] == 0 and arr[1] == 0:
        break
    map_size.append([arr[1],arr[0]])
    map_temp = []
    for i in range(arr[1]):
        temp = list(map(int, input().split()))
        map_temp.append(temp)
    map_arr.append(map_temp)

visit = []
for i in map_size:
    temp = [[0 for j in range(i[1])]for k in range(i[0])]
    visit.append(temp)


direction = [[0,-1],[-1,-1],[-1,0],[-1,1],[0,1],[1,-1],[1,0],[1,1]]

result = [0 for i in range(len(map_arr))]

def land_search(index, x, y,depth):
    if map_arr[index][x][y] == 0 or visit[index][x][y] == 1:
        return
    if depth == 0:
        result[index] += 1

    visit[index][x][y] =1
    for d in direction:
        dx = x + d[0]
        dy = y + d[1]
        if dx<0 or dy<0 or dx >= map_size[index][0] or dy>= map_size[index][1]:
            continue
        if map_arr[index][dx][dy] ==1 and visit[index][dx][dy] == 0:
            land_search(index,dx,dy,depth+1)


for index in range(len(map_arr)):
    for i in range(map_size[index][0]):
        for j in range(map_size[index][1]):
            land_search(index,i,j,0)

for i in result:
    print(i)


