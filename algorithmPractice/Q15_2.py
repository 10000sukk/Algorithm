from collections import deque
import sys

input = sys.stdin.readline


n, m, k, x = map(int, input().split())

INF = int(1e9)
graph = [[] for _ in range(n+1)]

distance = [INF]*(n+1)

visited = [False]*(n+1)

for _ in range(m):
    start, end = map(int, input().split())
    graph[start].append(end)

q = deque([x])
distance[x] = 0

while q:
    now = q.popleft()
    if distance[now] >= k:
        break
    visited[now] = True
    for next_node in graph[now]:
        if not visited[next_node]:
            distance[next_node] = distance[now] + 1
            visited[next_node] = True
            q.append(next_node)

result = [i for i in range(len(distance)) if distance[i] == k]
result.sort()
if len(result) == 0:
    print(-1)
else:
   [print(i) for i in result]
