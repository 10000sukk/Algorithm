n,m = map(int, input().split())
visit = [[0 for j in range(m)] for i in range(n)]

x,y,d = map(int, input().split())
array = []
for i in range(n):
    array.append(list(map(int, input().split())))

dx = [-1,0,1,0]
dy = [0,1,0,-1]

def turn_left():
    global d
    d -= 1
    if d < 0:
        d = 3

turn_count = 0
result = 0

while True:
    turn_left()
    turn_count += 1
    nx = x + dx[d]
    ny = y + dy[d]

    if visit[nx][ny] == 0 and array[nx][ny] == 0:
        x = nx
        y = ny
        turn_count = 0
        visit[nx][ny] = 1
        result += 1
        continue

    if turn_count == 4:
        nx = x - dx[d]
        ny = y - dy[d]

        if array[nx][ny] == 0:
            x = nx
            y = ny
            turn_count = 0
        else:
            break


print(result)


