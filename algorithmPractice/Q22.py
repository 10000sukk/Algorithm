from collections import deque


def solution(board):
    answer = 0
    n = len(board)
    start = [[0,0], [0,1], 0]
    result = bfs(board, start, n)
    return result

def bfs(board, start, n):
    result = 0
    visited = []
    target = [n-1, n-1]
    dx = [0,0,1,-1]
    dy = [1,-1,0,0]

    r_horizon_up = [[[-1, 1],[0, 0]], [[0, 0], [-1, -1]]]
    r_horizon_down = [[[0, 0],[1, -1]], [[1, 1],[0, 0]]]

    r_vertical_right = [[[0,0],[-1,1]],[[1,1],[0,0]]]
    r_vertical_left = [[[0,0],[-1,-1]],[[1,-1],[0,0]]]

    q = deque([start])
    visited.append([start[0], start[1]])

    while q:
        now1, now2, cost = q.popleft()
        #print("now1: ", now1, " now2: ", now2, "  cost: ", cost)
        if now1 == target or now2 == target:
            return cost

        if now1[0] == now2[0]:
            if now1[1] > now2[1]:
                now1, now2 = now2, now1
        else:
            if now1[0] > now2[0]:
                now1, now2 = now2, now1

        for i,j in zip(dx, dy):
            new1 = [a+b for a,b in zip(now1, [i,j])]
            new2 = [a+b for a,b in zip(now2, [i,j])]
            if new1[0] < 0 or new1[0] >= n or new1[1] < 0 or new1[1] >= n:
                continue
            if new2[0] < 0 or new2[0] >= n or new2[1] < 0 or new2[1] >= n:
                continue

            if [new1, new2] not in visited:
                if board[new1[0]][new1[1]] != 1 and board[new2[0]][new2[1]] != 1:
                    q.append([new1, new2, cost+1])
                    visited.append([new1, new2])

        #가로
        if now1[0] == now2[0]:
            #up
            if now1[0] -1 >= 0:
                if board[now1[0] -1][now1[1]] != 1 and board[now2[0] -1][now2[1]] != 1:
                    for rotation1, rotation2 in r_horizon_up:
                        new1 = [a+b for a,b in zip(now1, rotation1)]
                        new2 = [a+b for a,b in zip(now2, rotation2)]
                        if new1[0] > new2[0]:
                            new1, new2 = new2, new1
                        if [new1, new2] not in visited:
                            q.append([new1, new2, cost+1])
                            visited.append([new1, new2])

            #down
            if now1[0]+1 < n:
                if board[now1[0]+1][now1[1]] != 1 and board[now2[0]+1][now2[1]] != 1:
                    for rotation1, rotation2 in r_horizon_down:
                        new1 = [a+b for a,b in zip(now1, rotation1)]
                        new2 = [a+b for a,b in zip(now2, rotation2)]
                        if new1[0] > new2[0]:
                            new1, new2 = new2, new1
                        if [new1, new2] not in visited:
                            q.append([new1, new2, cost + 1])
                            visited.append([new1, new2])
        #세로
        else:
            #right
            if now1[1]+1 < n:
                if board[now1[0]][now1[1]+1] != 1 and board[now2[0]][now2[1]+1] != 1:
                    for rotation1, rotation2 in r_vertical_right:
                        new1 = [a+b for a,b in zip(now1, rotation1)]
                        new2 = [a+b for a,b in zip(now2, rotation2)]
                        if new1[1] > new2[1]:
                            new1, new2 = new2, new1
                        if [new1, new2] not in visited:
                            q.append([new1, new2, cost + 1])
                            visited.append([new1, new2])

            if now1[1]-1 >= 0:
                if board[now1[0]][now1[1]-1] != 1 and board[now2[0]][now2[1]-1] != 1:
                    for rotation1, rotation2 in r_vertical_left:
                        new1 = [a+b for a,b in zip(now1, rotation1)]
                        new2 = [a+b for a,b in zip(now2, rotation2)]
                        if new1[1] > new2[1]:
                            new1, new2 = new2, new1
                        if [new1, new2] not in visited:
                            q.append([new1, new2, cost + 1])
                            visited.append([new1, new2])

    return result






board = [[0, 0, 0, 1, 1],[0, 0, 0, 1, 0],[0, 1, 0, 1, 1],[1, 1, 0, 0, 1],[0, 0, 0, 0, 0]]
print(solution(board))