arr = list(map(int,input().split()))

result =[]
r = 0
lenth = arr[1]
while True:
    if lenth > 100:
        print(-1)
        break
    result = list(range(lenth))
    s = sum(result)
    if arr[0] - s < 0:
        print(-1)
        break
    if (arr[0] - s)%lenth == 0:
        r = int((arr[0] - s)/lenth)
        for i in range(lenth):
            result[i] += r
        for i in result:
            print(i, end=' ')
        break
    lenth += 1
