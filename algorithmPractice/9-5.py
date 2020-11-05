#전보
import heapq

INF = int(1e9)
n, m, c = map(int, input().split())

graph = [[] for _ in range(n+1)]
distance = [INF] * (n+1)

for _ in range(m):
    x, y, z = map(int, input().split())
    graph[x].append((y, z))

def dijkstra(start):
    q = []
    distance[start] = 0
    heapq.heappush(q,(distance[start], start))

    while q:
        dist, now = heapq.heappop(q)
        if distance[now] < dist:
            continue

        for i in graph[now]:
            cost = dist + i[1]
            if distance[i[0]] > cost:
                distance[i[0]] = cost
                heapq.heappush(q, (cost, i[0]))

dijkstra(c)

result1 = 0
result2 = 0
for i in range(1, n+1):
    if distance[i] < INF and i != c:
        result1 += 1

    if distance[i] > result2 and distance[i] != INF:
        result2 = distance[i]

print(result1, result2)


