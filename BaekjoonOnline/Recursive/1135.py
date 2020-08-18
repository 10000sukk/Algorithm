N = int(input())
arr = list(map(int,input().split()))


def find_Leaf(arr1):
    temp = [0 for i in range(N)]
    for i in range(len(arr1)):
        if arr1[i] == -1:
            continue
        temp[arr1[i]] += 1
    result = []
    for i in range(len(arr1)):
        if temp[i] == 0 and arr1[i] != -1:
            result.append(i)
    return result


def find_degree(arr1):
    result = [-1 for i in range(N)]
    temp = list(map(int, arr))
    temp_leaf = find_Leaf(temp)
    for i in temp_leaf:
        result[i] = 0
    while True:
        if len(temp_leaf) == 0:
            break
        temp_leaf = find_Leaf(temp)
        for i in temp_leaf:
            if result[arr[i]] < result[i] + 1:
                result[arr[i]] = result[i] + 1
        for i in temp_leaf:
            temp[i] = -1
        temp_leaf = find_Leaf(temp)

    return result

def solve_time(arr1):
    result = []
    arr1.sort(reverse=True)
    a = 1
    for i in arr1:
        result.append(i+a)
        a += 1
    result_max = 0
    for i in result:
        if result_max < i:
            result_max = i
    return result_max

tree_degree = find_degree(arr)

child = [[] for i in range(N)]
result = [0 for i in range(N)]

for i in range(1,N):
    child[arr[i]].append(i)

for i in range(tree_degree[0]):
    for j in range(N):
        if tree_degree[j] == i+1:
            tmp = []
            for k in child[j]:
                tmp.append(result[k])
            result[j] = solve_time(tmp)

print(result[0])






