from collections import deque
import copy

def solution(n,edges):
    answer = 0
    graph = [[] for _ in range(n)]
    for v1, v2 in edges:
        graph[v1].append(v2)
    print(graph)

    q = deque([0])
    visited = [False]*n
    visited[0] = True

    while q:
        cut(graph, q)

        q1 = deque([])
        while q:
            now_node = q.popleft()
            for next_node in graph[now_node]:
                q1.append(next_node)
        q = copy.deepcopy(q1)

    print(graph)
    answer = cal_count(graph,0)

    return answer

def cut(graph, queue):
    result = []

    for now_node in queue:
        for next_node in graph[now_node]:
            tmp = [now_node, next_node]
            tmp.append(cal_count(graph, next_node))
            result.append(tmp)
            print(tmp)
    print(result)
    if len(result) > 0:
        arr = max(result, key=lambda x:x[2])
        graph[arr[0]].remove(arr[1])

def cal_count(graph, start):
    count = 0
    q = deque([start])
    while q:
        now_node = q.popleft()
        count += 1
        for next_node in graph[now_node]:
            q.append(next_node)
    return count


n = 10
edges = [[0, 1], [0, 2], [1, 3], [2, 4], [2, 5], [2, 6], [3, 7], [3, 8], [3, 9]]
print(solution(n,edges))