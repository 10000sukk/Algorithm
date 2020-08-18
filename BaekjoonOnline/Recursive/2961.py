import sys

N = int(sys.stdin.readline())
arr =[]
for i in range(N):
    arr1 = list(map(int,sys.stdin.readline().split()))
    arr.append(arr1)

flag = [0 for i in range(N)]
result = []
b= 0
def cook(depth, N):
    if depth == N:
        S = 0
        B = 0
        a = 0
        for i in range(N):
            if flag[i] == 1:
                if a == 0:
                    S = arr[i][0]
                    a += 1
                else:
                    S *= arr[i][0]
                B += arr[i][1]
        if a == 0:
            return
        if S > B:
            result.append(S-B)
        else:
            result.append(B-S)
        return

    flag[depth] = 0
    cook(depth+1,N)
    flag[depth] = 1
    cook(depth+1 ,N)

cook(0,N)

answer = result[0]
for i in result:
    if answer > i:
        answer = i
print(answer)
