import sys

n = int(sys.stdin.readline())
m = int(sys.stdin.readline())

arr = []
for i in range(m):
    temp = list(map(int, sys.stdin.readline().split()))
    arr.append(temp)

friends = [[] for i in range(n+1)]
for i in arr:
    friends[i[0]].append(i[1])
    friends[i[1]].append(i[0])
result = [0 for i in range(n+1)]
result[1] =1
for i in friends[1]:
    result[i] =1
    for j in friends[i]:
        result[j] =1

n = 0
for i in range(2,len(result)):
    if result[i] ==1:
        n +=1


print(n)