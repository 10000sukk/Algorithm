import sys

L = int(sys.stdin.readline())
L_set = list(map(int,input().split()))
L_set.sort()
N = int(sys.stdin.readline())

def has_value(arr,n):
    arr1 = list(map(int, arr))
    a = len(set(arr1))
    arr1.append(n)
    if a == len(set(arr1)):
        return True
    else:
        return False

if has_value(L_set,N):
    print(0)
    sys.exit()

a = 0
b = 0
for i in range(L-1):
    if N > L_set[i] and N < L_set[i+1]:
        a = N - L_set[i] -1
        b = L_set[i+1] - N -1
if b ==0:
    b = L_set[0]-N -1
    a = N -1

result = a*b + a + b
# print('a:',a,' b:',b)
print(result)