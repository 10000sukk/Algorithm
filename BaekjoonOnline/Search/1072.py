import sys


arr = list(map(int,input().split()))
x = arr[0]
y = arr[1]
oldZ = y/x

if oldZ >= 0.99:
    print(-1)
    sys.exit()

k = float(format((oldZ+0.01),'.2f'))


result = (x*k-y)/(1-k)

if result == int(result):
    print(int(result))
else:
    print(int(result+1))


