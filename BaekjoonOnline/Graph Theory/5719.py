

result = []
while True:
    temp = list(map(int,input().split()))
    if(temp[0] == 0 and temp[1] == 0):
        break
    N = temp[0]
    M = temp[1]

    temp = list(map(int, input().split()))
    S = temp[0]
    V = temp[1]

    D = [[1001 for i in range(N)] for j in range(N)]

    for i in range(M):
        temp = list(map(int, input().split()))
        D[temp[0]][temp[1]] = temp[2]
    






