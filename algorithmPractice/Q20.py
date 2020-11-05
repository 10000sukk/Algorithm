from itertools import combinations

def isSafe(teacher, student, obstacle):
    for i,j in teacher:
        for x,y in zip(dx, dy):
            i1, j1 = i, j
            i1 += x
            j1 += y
            while i1 >= 0 and i1 < n and j1 >= 0 and j1 < n:
                if (i1,j1) in student:
                    return False
                elif (i1,j1) in obstacle:
                    break
                i1 += x
                j1 += y
    return True

n = int(input())

map_arr = []
for _ in range(n):
    map_arr.append(list(input().split()))

dx = [0,0,1,-1]
dy = [1,-1,0,0]

teacher = []
student = []
blank = []

for i in range(n):
    for j in range(n):
        if map_arr[i][j] == 'S':
            student.append((i,j))
        elif map_arr[i][j] == 'T':
            teacher.append((i,j))
        else:
            blank.append((i,j))

obstacle_case = list(combinations(blank, 3))

result = False
for obstable in obstacle_case:
    if isSafe(teacher, student, obstable):
        result = True
        break

if result:
    print("YES")
else:
    print("NO")




