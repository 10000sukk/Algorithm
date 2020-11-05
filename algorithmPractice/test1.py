from itertools import combinations
import copy
from collections import deque

def solution(n, edge):
    graph = [[] for _ in range(n)]
    degree = [0] * n
    for v1, v2 in edge:
        graph[v1].append(v2)
        graph[v2].append(v1)
        degree[v1] += 1
        degree[v2] += 1

    edge1 = copy.deepcopy(edge)
    for v1,v2 in enumerate(graph):
        if len(v2) == 1:
            if [v1, v2[0]] in edge1:
                edge1.remove([v1, v2[0]])
            elif [v2[0], v1] in edge1:
                edge1.remove([v2[0], v1])

    edge_cases = list(combinations(edge1, 2))
    print(edge_cases)
    result = []
    for edge_case in edge_cases:
        if check(graph, edge_case, int(n/3)) == True:
            for i,e in enumerate(edge):
                if e in edge_case:
                    result.append(i)
                elif [e[1], e[0]] in edge_case:
                    result.append(i)
            result.sort()
            return result
    return result



def check(graph1, edge, target):
    graph = copy.deepcopy(graph1)
    for v1, v2 in edge:
        graph[v1].remove(v2)
        graph[v2].remove(v1)
    visited = [False]*len(graph)
    result = []
    for i in range(len(graph)):
        result.append(bfs(graph, i, visited))
    result.sort(reverse=True)
    for i in range(3):
        if result[i] != target:
            return False
    return True

def bfs(graph, start, visited):
    result = 0
    if visited[start]:
        return 0
    visited[start] = True
    q = deque([start])
    while q:
        result += 1
        now_node = q.popleft()
        for next_node in graph[now_node]:
            if not visited[next_node]:
                q.append(next_node)
                visited[next_node] += 1

    return result



n = 9
edge = [[0,2], [2,1], [2,4], [3,5], [5,4], [5,7], [7,6], [6,8]]
print(solution(n,edge))




