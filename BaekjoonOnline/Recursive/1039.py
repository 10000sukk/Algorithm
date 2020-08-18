import sys

arr = list(sys.stdin.readline().split())
N = arr[0]
K = int(arr[1])
M = len(N)
if M < 2:
    print(-1)
    sys.exit()

N = list(map(int,N))

N1 = list(map(int,N))
N1.sort(reverse=True)

result =[]
def change_dfs(depth, arr):

    if depth == K:
        result.append(arrTonum(arr))
        return
    a = -1
    for i in range(M):
        if arr[i] != N1[i]:
            a = i
            break
    if a == -1:
        if M != len(set(arr)):
            print(arrTonum(arr))
            sys.exit()
        else:
            arr = change_index(arr,M-1,M-2)
            if arr[0] == 0:
                print(-1)
                sys.exit()
            else:
                change_dfs(depth+1,arr)
                return
    b_index = []
    for i in range(a+1,M):
        if N1[a] == arr[i]:
            b_index.append(i)
    for i in b_index:
        arr1 = list(map(int,arr))
        change_dfs(depth+1, change_index(arr1,a,i))





def change_index(arr,a,b):
    temp = arr[b]
    arr[b] = arr[a]
    arr[a] = temp
    return arr

def arrTonum(arr):
    arr.reverse()
    result = 0
    n = 0
    for i in arr:
        result += i*(10**n)
        n+=1
    return result


change_dfs(0,N)

result_max = 0
for i in result:
    if i > result_max:
        result_max = i
print(result_max)