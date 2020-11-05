#상하좌우
n = int(input())
direction = list(input().split())
row = 1
col =1

def check(n, d, r, c):
    if d == 'L':
        c -= 1
    elif d == 'R':
        c += 1
    elif d == 'U':
        r -= 1
    elif d == 'D':
        r += 1


    if r > 0 and r <= n and c >0 and c <=n:
        return [r, c]
    else:
        return False

for i in direction:
    if check(n,i,row, col) != False:
        temp = check(n,i,row,col)
        row = temp[0]
        col = temp[1]

print(row,col)