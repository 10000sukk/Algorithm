#큰 수의 법칙

n,m,k = map(int,input().split())
data = list(map(int, input().split()))

data.sort(reverse=True)
a = data[0]
b = data[1]

result = 0
count=0
flag = 0
for i in range(m):
    if count < k:
        result += a
        count += 1
    else:
        result += b
        count = 0

print(result)

