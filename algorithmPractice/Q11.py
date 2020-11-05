def find_tail_before(snake, r, c):
    pre_r, pre_c = r,c
    while True:
        r1, c1 = snake[r][c]
        if r1 == r and c1 == c:
            break
        pre_r, pre_c = r, c
        r, c = r1, c1
    return [pre_r, pre_c]

def find_tail(snake, r, c):
    while True:
        r1, c1 = snake[r][c]
        if r1 == r and c1 == c:
            break
        r, c = r1, c1
    return [r1, c1]


n = int(input())
k = int(input())
apple = [list(map(int, input().split())) for _ in range(k)]
l = int(input())
move = []
for _ in range(l):
    x,c = input().split()
    move.append([int(x), c])

map_list = [[0]*n for _ in range(n)]
for r,c in apple:
    map_list[r-1][c-1] = 2

map_list[0][0] = 1
time = 1
direction = [[0,1], [1,0], [0,-1], [-1, 0]] #동남서북
now_direction = 0
move_list = [0]*10001
snake = [[]*n for _ in range(n)]
head = [0,0]
for i in range(n):
    for j in range(n):
        snake[i].append([i,j])

for x,c in move:
    move_list[x] = c

while True:
    new_head = [i + j for i,j in zip(head, direction[now_direction])]
    if new_head[0] >= n or new_head[0] < 0 or new_head[1] >= n or new_head[1] < 0:
        break
    snake[new_head[0]][new_head[1]] = head
    head = new_head

    if map_list[new_head[0]][new_head[1]] == 2:
        map_list[new_head[0]][new_head[1]] = 1

    elif map_list[new_head[0]][new_head[1]] == 0:
        map_list[new_head[0]][new_head[1]] = 1
        tail = find_tail(snake, new_head[0], new_head[1])
        new_tail = find_tail_before(snake, new_head[0], new_head[1])
        snake[new_tail[0]][new_tail[1]] = new_tail
        map_list[tail[0]][tail[1]] = 0

    elif map_list[new_head[0]][new_head[1]] == 1:
        break

    if move_list[time] == 'L':
        now_direction -= 1
        now_direction %= 4
    elif move_list[time] == 'D':
        now_direction += 1
        now_direction %= 4
    time += 1

print(time)



