from bisect import bisect_left

l = int(input())
arr = list(map(int, input().split()))
arr.sort()
n = int(input())
if n in arr:
    print(0)
else:
    index = bisect_left(arr,n)
    if index == 0:
        a = 0
        b = arr[index]
    else:
        a = arr[index-1]
        b = arr[index]

    result = (n-a)*(b-n) - 1
    print(result)

