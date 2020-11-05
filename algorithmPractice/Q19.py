from itertools import permutations

def solve(numbers, operator):
    result = numbers[0]
    for n,oper in zip(numbers[1:], operator):
        if oper == "+":
            result += n
        elif oper == "-":
            result -= n
        elif oper == "*":
            result *= n
        else:
            if result >= 0:
                result //= n
            else:
                result = -result
                result //= n
                result = - result
    return result



n = int(input())
numbers = list(map(int, input().split()))
operators_arr = list(map(int, input().split()))
operators = []
for i in range(len(operators_arr)):
    if i == 0:
        operators.extend(["+" for _ in range(operators_arr[i])])
    elif i ==1:
        operators.extend(["-" for _ in range(operators_arr[i])])
    elif i == 2:
        operators.extend(["*" for _ in range(operators_arr[i])])
    elif i == 3:
        operators.extend(["/" for _ in range(operators_arr[i])])

operators_case = list(permutations(operators, len(operators)))
operators_case = list(set(operators_case))

result = []
for i in operators_case:
    result.append(solve(numbers, i))

print(max(result))
print(min(result))

