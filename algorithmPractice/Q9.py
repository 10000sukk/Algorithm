# def solution(s):
#     arr = [compression(s, i) for i in range(1,len(s)//2 + 1)]
#     answer = min(arr)
#     print(arr)
#     return answer
#
#
# def compression(string, n):
#     s_list = []
#     s = string[0]
#     for i in range(1,len(string)):
#         if i%n == 0:
#             s_list.append(s)
#             s = ""
#         s += string[i]
#     s_list.append(s)
#
#     s_list.append(" ")
#     print(s_list)
#     result = []
#     pre = ""
#     count = 1
#     for now in s_list:
#         if pre == now:
#             count += 1
#
#         else:
#             if count > 1:
#                 result.extend([str(count), pre])
#             else:
#                 result.append(pre)
#             count = 1
#         pre = now
#
#     print(result)
#     return len("".join(result))
#
# print(solution(input()))


#############################################################
####geneator 객체를 조금만 더 공부하면 엄청 간결하게 풀 수 있는 문제!!####
#############################################################
def solution(s):
    return min(compression(s,i) for i in range(1,len(s)//2 + 1))

def compression(text, n):
    words = [text[i: i+n] for i in range(0, len(text), n)]
    result = []
    cur_word = words[0]
    cur_cnt = 1
    for a,b in zip(words, words[1:] + ['']):
        if a == b:
            cur_cnt += 1
        else:
            result.append([cur_word, cur_cnt])
            cur_word = b
            cur_cnt = 1

    return sum(len(word) + (len(str(cnt)) if cnt > 1 else 0) for word, cnt in result)

a = [
    "aabbaccc",
    "ababcdcdababcdcd",
    "abcabcdede",
    "abcabcabcabcdededededede",
    "xababcdcdababcdcd",

    'aaaaaa',
]

for x in a:
    print(solution(x))