s = list(map(int, input()))

result = s[0]
for i in range(1,len(s)):
    if result == 1 or result == 0:
        result += s[i]
    else:
        result *= s[i]

print(result)
