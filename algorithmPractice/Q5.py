def combi(n,m):
    if n < m:
        return 0
    result = 1
    for i in range(n, n-m, -1):
        result *= i

    return int(result/factorial(m))


def factorial(n):
    if n == 0:
        return 1
    return n*factorial(n-1)

n, m = map(int, input().split())
data = list(map(int, input().split()))

w = [0]*(m+1)


for i in data:
    w[i] += 1

result = combi(n,2)

for i in w:
    result -= combi(i,2)
print(result)
