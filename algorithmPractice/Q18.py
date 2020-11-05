def solution(p):
    answer = solve(p)
    return answer

def solve(string):
    if len(string) == 0:
        return ""
    u,v = split_s(string)
    if isProper(u):
        return u + solve(v)
    else:
        tmp = ""
        tmp += "("
        tmp += solve(v)
        tmp += ")"
        u = u[1:-1]
        for i in u:
            if i == "(":
                tmp += ")"
            else:
                tmp += "("
        return tmp


def split_s(string):
    first = string[0]
    result = 1
    index = 0
    for i in range(1, len(string)):
        if string[i] == first:
            result += 1
        else:
            result -= 1
        if result == 0:
            index = i
            break
    return [string[:index+1], string[index+1:]]

def isBlanced(string):
    result = 0
    for s in string:
        if s == "(":
            result += 1
        else:
            result -= 1
    return True if result == 0 else False

def isProper(string):
    if not isBlanced(string):
        return False
    if string[0] != "(":
        return False
    result = 1
    for s in string[1:]:
        if s == "(":
            result += 1
        else:
            result -= 1

        if result < 0:
            return False
    return True


p = "()))((()"
print(solution(p))