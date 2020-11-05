from itertools import combinations

def cal_chickendistance(x, y, chicken):
    result = [(abs(x - i) + abs(y - j)) for i, j in chicken]
    return min(result)


def cal_allchickendistance(home, chicken):
    result = [cal_chickendistance(x, y, chicken) for x, y in home]
    return sum(result)


def delete_chicken(home, chicken, m):
    result = []
    combi = list(combinations(chicken, m))

    for c in combi:
        result.append(cal_allchickendistance(home, c))

    answer = result[0]
    location = 0
    for i in range(1, len(result)):
        if answer > result[i]:
            answer = result[i]
            location = i

    return list(combi[location])


n, m = map(int, input().split())
arr = [list(map(int, input().split())) for _ in range(n)]

home = []
chicken = []

for i in range(len(arr)):
    for j in range(len(arr)):
        if arr[i][j] == 1:
            home.append([i, j])
        elif arr[i][j] == 2:
            chicken.append([i, j])

chicken = delete_chicken(home, chicken, m)

print(cal_allchickendistance(home, chicken))



