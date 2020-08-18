N = int(input())
n=N
number = []
while n!=0:
    a = n%10
    number.append(a)
    n = int(n/10)
sum = 0
for i in number:
    sum += i
if sum%3 != 0:
    print(-1)
else:
    number.sort(reverse=True)
    result = 0
    for i in number:
        result = result*10 + i
    print(result)