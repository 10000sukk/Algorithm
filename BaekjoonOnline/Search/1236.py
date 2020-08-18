import sys

arr = list(map(int, input().split()))
row = arr[0]
col = arr[1]
castle = []

for i in range(row):
    castle.append(list(input()))

row1 = [0 for i in range(row)]
col1 = [0 for i in range(col)]


for i in range(row):
    for j in range(col):
        if castle[i][j] == 'X':
            row1[i] = 1
            col1[j] = 1

row1_n = 0
col1_n = 0

for i in range(row):
    if row1[i] == 0:
        row1_n += 1


for i in range(col):
    if col1[i] == 0:
        col1_n += 1

if row1_n > col1_n:
    print(row1_n)
else:
    print(col1_n)