import copy

def solution(key, lock):
    n = len(lock)
    m = len(key)

    lock2 = [[0]*(n+ 2*m -2) for _ in range(n + 2*m -2)]
    for i in range(n):
        for j in range(n):
            if lock[i][j] == 1:
                lock2[i + m -1][j + m -1] = 1

    for _ in range(4):
        for i in range(m + n -1):
            for j in range(m + n -1):
                if key_test(lock2, key, i, j) == True:
                    print(key)
                    return "true"
        key = lotation(key)
    return "false"

#시계방향 90도 회전
def lotation(key):
    length = len(key)
    result = [[0]*length for _ in range(length)]
    for i in range(length):
        for j in range(length):
            if key[i][j] == 1:
                result[j][length-i-1] = 1
    return result

def key_test(lock2, key, r, c):
    len_key = len(key)
    len_lock2 = len(lock2)
    lock3 = copy.deepcopy(lock2)
    for i in range(len_key):
        for j in range(len_key):
            if key[i][j] == 1:
                lock3[i+r][j+c] += 1
    for i in range(len_key-1, len_lock2 - len_key + 1):
        for j in range(len_key-1, len_lock2 - len_key + 1):
            if lock3[i][j] != 1:
                return False
    print("r: {0} , c: {1}".format(r,c))
    print("key")
    print(key)
    return True


key = [[0, 0, 1], [0, 0, 1], [1, 1, 1]]
lock = [[1, 1, 1, 1, 1], [0, 1, 1, 1, 1], [0, 1, 1, 1, 1], [0, 0, 0, 1, 1], [1, 1, 1, 1, 1]]
print(solution(key, lock))