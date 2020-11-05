#떡볶이 떡 만들기

def sumOfcut(array, length):
    result = 0
    for i in array:
        if length < i:
            result += i-length
    return result

def binarySearch(array, target, start, end):
    global result
    while start <= end:
        mid = (start + end) // 2
        temp = sumOfcut(array, mid)
        if temp == target:
            result.append(mid)
            return

        elif temp > target:
            result.append(mid)
            start = mid + 1

        else:
            end = mid - 1
    return


result = []


n, m = map(int, input().split())
arr = list(map(int, input().split()))

binarySearch(arr, m, 0, max(arr))

print(max(result))