#숫자 카드 게임
n,m= map(int, input().split())
card = []
for i in range(n):
    card.append(list(map(int, input().split())))
result = []
for i in card:
    result.append(min(i))
print(max(result))
