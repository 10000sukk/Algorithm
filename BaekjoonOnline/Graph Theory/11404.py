import sys

n = int(sys.stdin.readline())
m = int(sys.stdin.readline())

bus_fee = [[9900001 for i in range(n)] for j in range(n)]
for i in range(m):
    arr = list(map(int,sys.stdin.readline().split()))
    if bus_fee[arr[0]-1][arr[1]-1] > arr[2]:
        bus_fee[arr[0]-1][arr[1]-1] = arr[2]

def min_fee(matrix):
    while True:
        a = 0
        for i in range(n):
            for j in range(n):
                for k in range(n):
                    if matrix[i][j] > matrix[i][k] + matrix[k][j]:
                        a = 1
                        matrix[i][j] = matrix[i][k] + matrix[k][j]
        if a == 0:
            return

min_fee(bus_fee)
for i in range(n):
    for j in range(n):
        if i == j or bus_fee[i][j] > 9900000:
            print(0,end=' ')
        else:
            print(bus_fee[i][j],end=' ')
    print()

