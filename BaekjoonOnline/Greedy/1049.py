import re

arr1 = re.findall('\d+',input())
arr1 = list(map(int,arr1))
N = arr1[0]
M = arr1[1]
result = 0
arr = []
for i in range(M):
    arr1 = re.findall('\d+', input())
    arr1 = list(map(int,arr1))
    arr.append(arr1)

single_price = arr[0][1]
set_price = arr[0][0]

for i in arr:
    if i[0] < set_price:
        set_price = i[0]
    if i[1] < single_price:
        single_price = i[1]

if single_price*6 < set_price:
    six_price = single_price*6
else:
    six_price = set_price
if (N%6)*single_price < set_price:
    result += (N%6)*single_price
else:
    result += set_price
result += six_price*int(N/6)


print(result)




