import re

N = int(input())
arr = list(map(int,input().split()))
K = int(input())



def delete(k):
    arr[k] = -2

def searchLeaf(k):
    for i in arr:
        if i == k:
            return False
    k1 = k
    while True:
        if arr[k1] == -2:
            return False
        if arr[k1] == -1:
            return True
        k1 = arr[k1]
delete(K)
result = 0
for i in range(len(arr)):
    if searchLeaf(i) == True:
        result += 1
print(result)

