import sys

n = int(sys.stdin.readline())
n_count = int(sys.stdin.readline())

result = 0
if n == 1:
    result = n_count*8
elif n == 5:
    result = n_count*8 + 4
else:
    if n_count%2 == 0:
        result = ((n_count)/2)*8 + (n-1)
    else:
        result = ((n_count-1)/2)*8 + (9-n)

print(int(result))

