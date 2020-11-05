#개미전사

n = int(input())
k = list(map(int, input().split()))

d = [0]*(n+1)

k.append(0)

def fun1(x):
    if x<0:
        return 0
    if d[x] != 0:
        return d[x]
    result = max(fun1(x-2)+k[x], fun1(x-3)+k[x])
    d[x] = result
    return result

print(max(fun1(n-1), fun1(n-2)))