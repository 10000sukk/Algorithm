#기본적인 서로서 집합 알고리즘 소스코드

def find_parent(parent, x):
    #특정 노드가 아니라면, 루트 노드를 찾을 때까지 재귀적으로 호출
    if parent[x] != x:
        return find_parent(parent, parent[x])
    else:
        return x

#경로 압축 기법으로 시간 복잡도를 개선하는 find_parent 함수
def path_compression_find_parent(parent, x):
    if parent[x] != x:
        parent[x] = path_compression_find_parent(parent, parent[x])
    return parent[x]



#두 원소가 속한 집합을 합치기
def union_parent(parent, a, b):
    a = find_parent(parent, a)
    b = find_parent(parent, b)

    if a < b:
        parent[b] = a
    else:
        parent[a] = b


#노드의 개수와 간선(union 연산)의 개수 입력받기
v, e = map(int, input().split())
parent = [i for i in range(v+1)]

for i in range(e):
    a, b = map(int, input().split())
    union_parent(parent, a, b)

print('각 원소가 속한 집합: ', end=' ')
for i in range(1, v+1):
    print(path_compression_find_parent(parent, i), end=" ")

print()

print('부모테이블: ', end=" ")
for i in range(1, v+1):
    print(parent[i], end=" ")