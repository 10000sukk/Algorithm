import re


N = int(input())
arr = []
for i in range(N):
    templist = re.findall('\d+', input())
    arr.append(templist)

list = []
for i in range(N):
    list.append(0)

maxtime = 0
for i in range(N):
    if maxtime < int(arr[i][1]):
        maxtime = int(arr[i][1])

time = []
for i in range(maxtime):
    time.append(0)

def schedule(start, end):
    for i in range(start, end):
        time[i] += 1

result = []

def F(depth, N):
    if depth == N:
        for i in range(maxtime):
            time[i] = 0
        for i in range(N):
            if list[i] == 1:
                schedule(int(arr[i][0]), int(arr[i][1]))
        for i in range(maxtime):
            if time[i] > 1:
                return
        n = 0
        for i in range(N):
            if list[i] == 1:
                n += 1
        result.append(n)
        return
    list[depth] = 0
    F(depth+1, N)
    list[depth] = 1
    F(depth+1, N)

F(0,N)

max = 0
for i in range(len(result)):
    if max < result[i]:
        max = result[i]


print(max)
