import sys

testcase = []

while True:
    n = int(sys.stdin.readline())
    if n == 0:
        break
    else:
        testcase.append(n)

dp = [[-1 for i in range(31)] for j in range(31)]

def solve(n, depth,W,H):
    if depth == 2*n:
        return 1
    if depth == 0:
        W = n
        H = 0
    result = 0
    ret = 0
    if W > 0:
        if dp[W-1][H+1] != -1:
            result += dp[W-1][H+1]
        else:
            ret = solve(n, depth + 1, W - 1, H + 1)
            dp[W-1][H+1] = ret
            result += ret

    if H > 0:
        if dp[W][H - 1] != -1:
            result += dp[W][H - 1]
        else:
            ret = solve(n, depth + 1, W, H - 1)
            dp[W][H - 1] = ret
            result += ret

    return result

for i in testcase:
    print(solve(i,0,i,0))