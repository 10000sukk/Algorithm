import re

N = int(input())
arr = re.findall('\d+',input())
arr = list(map(int,arr))
arr.sort()
arr1 = []
a = 0
for i in arr:
    arr1.append(i)
    if a+1 < i:
        break
    else:
        a += i

print(a+1)




