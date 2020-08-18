#
# N = int(input())
# arr = list(map(int,input().split()))
# def find_Leaf(arr1):
#     temp = [0 for i in range(N)]
#     for i in range(len(arr1)):
#         if arr1[i] == -1:
#             continue
#         temp[arr1[i]] += 1
#     result = []
#     for i in range(len(arr1)):
#         if temp[i] == 0 and arr1[i] != -1:
#             result.append(i)
#     return result
#
#
# def find_degree(arr1):
#     result = [-1 for i in range(N)]
#     temp = list(map(int, arr))
#     temp_leaf = find_Leaf(temp)
#     print(temp_leaf)
#     for i in temp_leaf:
#         result[i] = 0
#     while True:
#         if len(temp_leaf) == 0:
#             break
#         temp_leaf = find_Leaf(temp)
#         for i in temp_leaf:
#             if result[arr[i]] < result[i] + 1:
#                 result[arr[i]] = result[i] + 1
#         for i in temp_leaf:
#             temp[i] = -1
#         temp_leaf = find_Leaf(temp)
#
#     return result
#
# print(find_degree(arr))

arr = [[] for i in range(10)]
arr[2].append(4)
print(arr)