import heapq

def solution(food_times, k):
    if sum(food_times) <= k:
        return -1

    length = len(food_times)
    count = 0
    h = []
    for i in range(len(food_times)):
        heapq.heappush(h, (food_times[i], i))

    while h:
        time, now = heapq.heappop(h)
        if (time-count)*length > k:
            heapq.heappush(h, (time, now))
            break
        else:
            k = k - (time-count)*length
            length -= 1
            count = time

    arr = sorted(h, key=lambda x:x[1])
    return arr[k % length][1] + 1




print(solution([8,6,4], 15))