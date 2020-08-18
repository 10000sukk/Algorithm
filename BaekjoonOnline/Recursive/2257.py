import sys

s = sys.stdin.readline()
s = list(s)
del s[-1]
stack = [0]
h = 0

def push(n):
    global h
    h += 1
    if len(stack)-1 < h:
        stack.append(0)
    stack[h] = n

def pop():
    global h
    n = stack[h]
    h -= 1
    return n

def plus(n):
    stack[h] += n


temp = 0
for i in range(len(s)):
    if s[i] == 'H':
        temp = 1
        plus(1)
    elif s[i] == 'C':
        temp = 12
        plus(12)
    elif s[i] == 'O':
        temp = 16
        plus(16)

    elif s[i] == '(':
        push(0)
    elif s[i] == ')':
        temp = pop()
        plus(temp)
    else:
        n = int(s[i])
        plus(temp*(n-1))
print(stack[0])


