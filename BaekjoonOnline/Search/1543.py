doc = input()

word = input()
result = 0
i=0
while True:

    if i + len(word) > len(doc):
        break

    temp = doc[i:i+len(word)]

    if word == temp:
        result += 1
        i += len(word)
    else:
        i += 1

print(result)
