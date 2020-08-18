import re

room_count = int(input())
arr = []
for i in range(room_count):
    arr1 = re.findall('\d+', input())
    arr1 = list(map(int,arr1))
    arr.append(arr1)

arr.sort(key=lambda x:x[0])
arr.sort(key=lambda x:x[1])

result = 0
start_min = arr[0][0]
end_max = arr[0][1]
for i in arr:
    if i[0] < start_min:
        start_min = i[0]
    if i[1] > end_max:
        end_max = i[1]

start = start_min
for i in arr:
    if start <= i[0]:
        result += 1
        start = i[1]
        

print(result)


