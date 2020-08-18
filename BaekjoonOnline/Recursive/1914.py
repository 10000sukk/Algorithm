import sys

n = int(sys.stdin.readline())

def count(n):
    if n == 1:
        return 1
    return 2*count(n-1) +1
print(count(n))

def move(start,end):
    print(start,end)

def hanoi(n,start,end,via):
    if n == 1:
        move(start,end)
    else:
        hanoi(n-1,start,via,end)
        move(start,end)
        hanoi(n-1,via,end,start)

if n <= 20:
    hanoi(n,1,3,2)




