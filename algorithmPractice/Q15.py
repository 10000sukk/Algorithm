import heapq
import sys


n, m, k, x = map(int, sys.stdin.readline().split())

INF = int(1e9)
graph = [[] for _ in range(n+1)]

distance = [INF]*(n+1)

for _ in range(m):
    start, end = map(int, sys.stdin.readline().split())
    graph[start].append(end)

def dijkstra(start):
    q = []
    heapq.heappush(q,(0, start))
    distance[start] = 0

    while q:
        dist, now = heapq.heappop(q)
        if dist >= k:
            return

        if dist > distance[now]:
            continue

        for i in graph[now]:
            cost = dist + 1
            if cost < distance[i]:
                distance[i] = cost
                heapq.heappush(q, (cost, i))

dijkstra(x)
result = [i for i in range(len(distance)) if distance[i] == k]
if len(result) == 0:
    print(-1)
else:
    result.sort()
    for i in result:
        print(i)




