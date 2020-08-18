
name = input()

N = int(input())
name_arr = []
for i in range(N):
    name_arr.append(input())


love_arr = []

def love_count(str):
    temp = [0,0,0,0]
    str1 = list(str)
    for i in str1:
        if i == 'L':
            temp[0] += 1
        elif i == 'O':
            temp[1] += 1
        elif i == 'V':
            temp[2] += 1
        elif i == 'E':
            temp[3] += 1

    return temp

love_arr.append(love_count(name))
for i in name_arr:
    love_arr.append(love_count(i))

def solve(arr1, arr2):
    L = arr1[0] + arr2[0]
    O = arr1[1] + arr2[1]
    V = arr1[2] + arr2[2]
    E = arr1[3] + arr2[3]
    return ((L+O)*(L+V)*(L+E)*(O+V)*(O+E)*(V+E)) % 100

result = [0]
for i in range(1,N+1):
    result.append(solve(love_arr[0], love_arr[i]))

result_max = result[0]
index = []
for i in range(1,N+1):
    if result[i] > result_max:
        index.clear()
        result_max = result[i]
        index.append(i-1)
    elif result[i] == result_max:
        index.append(i-1)

date = []
for i in index:
    date.append(name_arr[i])
date.sort()
print(date[0])


