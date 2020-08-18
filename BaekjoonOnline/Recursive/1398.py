import sys

N = int(sys.stdin.readline())
testcase = []
for i in range(N):
    testcase.append(int(sys.stdin.readline()))

def solve(n):
    tmp = []
    while True:
        if n == 0:
            break
        tmp.append(n%10)
        n = int(n/10)
    result = 0
    for i in range(len(tmp)-1,0,-1):
        a = tmp[i]*10 + tmp[i-1]
        b = a
        if a >= 75:
            b -= 75
            if int(b/10) + b%10 + 3 < tmp[i] + tmp[i-1]:
                result += 3
                tmp[i] = int(b/10)
                tmp[i-1] = b%10
        elif a >= 50:
            b -= 50
            if int(b / 10) + b % 10 + 2 < tmp[i] + tmp[i - 1]:
                result += 2
                tmp[i] = int(b / 10)
                tmp[i - 1] = b % 10
        elif a >= 25:
            b -= 25
            if int(b / 10) + b % 10 + 1 < tmp[i] + tmp[i - 1]:
                result += 1
                tmp[i] = int(b / 10)
                tmp[i - 1] = b % 10
    for i in tmp:
        result += i

    return result

for i in testcase:
    # print(i,'의 값은: ',solve(i))
    print(solve(i))

# 실패 했다 다시 풀기