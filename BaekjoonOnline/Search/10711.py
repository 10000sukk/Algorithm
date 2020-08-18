
arr = list(map(int,input().split()))
H = arr[0]
W = arr[1]

sand_castle = []
for i in range(H):
    temp = list(input())
    sand_castle.append(temp)


def solve():
    wave_power = [[0 for i in range(W)] for j in range(H)]
    for i in range(H):
        for j in range(W):
            if sand_castle[i][j] == '.':
                for ii in range(i-1,i+2):
                    for jj in range(j-1, j+2):
                        try:
                            wave_power[ii][jj] += 1
                        except:
                            continue
    a = 0

    for i in range(1,H-1):
        for j in range(1,W-1):
            if sand_castle[i][j] == '.' or sand_castle[i][j] == '9':
                continue
            else:
                if wave_power[i][j] >= int(sand_castle[i][j]):
                    a = 1
                    sand_castle[i][j] = '.'

    if a == 1:
        return True
    else:
        return False

result = 0
while True:
    if solve() == True:
        result += 1
    else:
        break
print(result)
