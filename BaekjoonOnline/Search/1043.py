arr = list(map(int, input().split()))
N = arr[0]
M = arr[1]

truth = list(map(int,input().split()))
truth_n = truth[0]
del truth[0]

person_value = [0 for i in range(N+1)]
for i in truth:
    person_value[i] = 1

party = []
party_n = []
for i in range(M):
    tmp = list(map(int, input().split()))
    party_n.append(tmp[0])
    del tmp[0]
    party.append(tmp)


result =[]
def solve(depth , result1,person):
    if depth == M:
        result.append(result1)
        return

    a = 0
    b = 0
    for i in party[depth]:
        if person[i] == 1:
            a =1
        elif person[i] == -1:
            b = 1

    person1 = list(map(int,person))

    if a == 1 and b == 0:
        for i in party[depth]:
            person1[i] = 1
        solve(depth+1, result1, person1)

    elif a == 0 and b == 1:
        for i in party[depth]:
            person1[i] = -1
        solve(depth+1, result1+1, person1)

    elif a== 0 and b == 0:
        for i in party[depth]:
            person1[i] = 1
        solve(depth + 1, result1, person1)

        person1 = list(map(int, person))
        for i in party[depth]:
            person1[i] = -1
        solve(depth+1, result1+1, person1)

    else :
        return

solve(0,0,person_value)

k = 0
for i in result:
    if k < i:
        k = i
print(k)







