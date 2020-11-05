from collections import Counter

def solution(N, stages):
    answer = []
    counter = Counter(stages)
    counter = sorted(counter.items(), key=lambda x:-x[0])

    user = [0]*(N+2)


    index = 0
    for i in range(N+1, 0, -1):
        if counter[index][0] == i:
            user[i] += counter[index][1]
            if index +1 < len(counter):
                index += 1
        if i != N+1:
            user[i] += user[i+1]

    result = [0]*(N+1)
    for i in range(1,N+1):
        if user[i] != 0:
            result[i] = (user[i] - user[i+1])/user[i]

    tmp = dict()
    for i in range(1,N+1):
        tmp[i] = result[i]

    tmp = sorted(tmp.items(), key=lambda x:-x[1])
    for i in tmp:
        answer.append(i[0])

    return answer

n = 5
stages = [2, 1, 2, 6, 2, 4, 3, 3]
solution(n, stages)