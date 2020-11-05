#1이 될때 까지
n,m = map(int, input().split())
count = 0
while n != 1:
    if n%m == 0:
        n /= m
        count +=1
    else:
        n -=1
        count += 1

print(count)
