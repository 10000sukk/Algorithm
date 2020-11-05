s = input()
s_result = []
n_result = 0
for i in s:
    if i.isdigit():
        n_result += int(i)
    else:
        s_result.append(i)
s_result.sort()

print("".join(s_result)+str(n_result))