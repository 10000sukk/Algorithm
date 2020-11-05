n = int(input())
array = []
for i in range(n):
    data = input().split()
    array.append((data[0], int(data[1])))

array.sort(key= lambda x: x[1])

for i in array:
    print(i[0], end=' ')
