#효율적인 화폐 구성

n, m = map(int, input().split())
d = [10001]*(m+1)
d[0] = 0

coin = []
for i in range(n):
    coin.append(int(input()))

coin.sort()
for i in coin:
    for j in range(i, m + 1):
        d[j] = min(d[j-i] + 1, d[j])


if d[m] == 10001:
    print(-1)
else:
    print(d[m])
