n = int(input())
arr = list(map(int, input().split()))

arr.sort()

result = 0

count = 0

for i in arr:
    count += 1
    if count >= i:
        result += 1
        count = 0

print(result)