from itertools import permutations

def solution(n, weak, dist):
    answer = 0
    length = len(weak)
    for i in range(length):
        weak.append(weak[i]+n)

    answer = len(dist)+1
    #각 weak 을 시작 위치로 지정하고 탐색
    for start in range(length):
        for friends in list(permutations(dist, len(dist))):
            count = 1

            position = weak[start] + friends[count-1]

            for index in range(start, start + length):

                if weak[index] > position:
                    count += 1
                    if count > len(dist):
                        break
                    position = weak[index] + friends[count-1]
            answer = min(answer, count)

    if answer > len(dist):
        return -1

    return answer


