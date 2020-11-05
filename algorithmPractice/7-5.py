import sys


def binarySearch(array, target, start, end):
    while start <= end:
        mid = (start + end) // 2

        if array[mid] == target:
            return "yes"

        elif target > array[mid]:
            start = mid + 1

        else:
            end = mid - 1
    return "no"


n = int(input())
arr1 = list(map(int, input().split()))

m = int(input())
arr2 = list(map(int, input().split()))

for i in arr2:
    print(binarySearch(arr1, i, 0, n-1), end=" ")




