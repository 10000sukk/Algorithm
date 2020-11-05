#왕실의 나이

location = input()

row = int(location[1])
if location[0] == 'a':
    col = 1
elif location[0] == 'b':
    col=2
elif location[0] == 'c':
    col=3
elif location[0] == 'd':
    col =4
elif location[0] == 'e':
    col=5
elif location[0] == 'f':
    col = 6
elif location[0] == 'g':
    col =7
elif location[0] == 'h':
    col =8


#모범 풀이
#col = int(ord(location[0])) - int(ord('a')) + 1



dx = [2,2,1,-1,-2,-2,1,-1]
dy = [-1,1,2,2,1,-1,-2,-2]

result = 0
for i in range(len(dx)):
    nx = row + dx[i]
    ny = col + dy[i]

    if nx < 1 or nx > 8 or ny < 1 or ny > 8:
        continue
    else:
        result += 1

print(result)