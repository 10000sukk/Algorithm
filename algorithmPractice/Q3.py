s = list(map(int, input()))

a = 0
b = 0

old = -1
for new in s:
    if old == new:
        continue
    old = new
    if new == 0:
        a += 1
    else:
        b += 1

if a > b:
    print(b)
else:
    print(a)