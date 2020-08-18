import re

N = int(input())
T = []
P = []

for i in range(N):
    a = re.findall('\d+',input())
    T.append(int(a[0]))
    P.append(int(a[1]))

def payoff(day, N, Tlist, Plist):
    if day >= N:
        return 0

    a = payoff(day + 1, N, Tlist, Plist)
    if day + Tlist[day] <= N:
        b = int(Plist[day]) + payoff(day + Tlist[day], N, Tlist, Plist)
        if a > b:
            return a
        else:
            return b
    return a


result = payoff(0, N, T, P)
print(result)


