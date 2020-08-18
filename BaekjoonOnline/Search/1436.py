N = int(input())
arr = []
n = 666
while True:
    if str(n).count('666') > 0:
        arr.append(n)
    n += 1
    if len(arr) == N:
        break
print(arr[-1])