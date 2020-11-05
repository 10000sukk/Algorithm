#1로 만들기
import sys

sys.setrecursionlimit(10**8)

x = int(input())

d = [0]*30001

def fun1(x):
    if x == 1:
        return 0

    if d[x] != 0:
        return d[x]

    temp = []
    if x % 5 == 0:
        temp.append(fun1(x//5) + 1)
    if x % 3 == 0:
        temp.append(fun1(x//3) + 1)
    if x % 2 == 0:
        temp.append(fun1(x//2) + 1)
    temp.append(fun1(x-1) + 1)

    result = min(temp)
    d[x] = result
    return result

print(fun1(x))
