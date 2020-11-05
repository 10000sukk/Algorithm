def solution(n, build_frame):
    result = []

    for r,c,a,b in build_frame:
        if b == 0:
            if [r,c,a] not in result:
                continue
            result.remove([r,c,a])
            if not check(result):
                result.append([r,c,a])
        elif b == 1:
            if [r,c,a] in result:
                continue
            result.append([r,c,a])
            if not check(result):
                result.remove([r,c,a])

    result.sort()

    return result

def check(result):
    for r,c,stuff in result:
        if stuff == 0:
            if c == 0 or [r,c-1,0] in result or [r-1,c,1] in result or [r,c,1] in result:
                continue
            return False
        elif stuff ==1:
            if [r,c-1,0] in result or [r+1,c-1,0] in result or([r-1,c,1] in result and [r+1,c,1] in result):
                continue
            return False
    return True



# def create_pillar(edge, result,r, c):
#     if [r, c, 0] in result:
#         return
#
#     if c == 0 or (edge[r][c][0] == True) or (edge[r][c][1] == True):
#         edge[r][c+1][0] = True
#         result.append([r,c,0])
#     return
#
#
# def create_beam(edge, result, r, c):
#     if [r, c, 1] in result:
#         return
#
#     if edge[r][c][0] == True or edge[r+1][c][0] == True:
#         edge[r][c][1] = True
#         edge[r+1][c][1] = True
#         result.append([r,c,1])
#         return
#
#     elif edge[r][c][1] == True and edge[r+1][c][1] == True:
#         result.append([r,c,1])
#         return
#     return
#
#
# def delete_pillar(edge, result, r, c):
#     if [r, c, 0] not in result:
#         return
#
#     if ([r,c+1,0] in result) and ([r, c+1, 1] not in result) and ([r,c-1 , 1] not in result):
#         return
#     elif ([r,c+1,1] in result) and([r+1, c, 0] not in result):
#         return
#
#     elif ([r-1, c+1 ,1] in result) and ([r, c+1 ,1] not in result) and([r-1, c, 0] not in result):
#         return
#
#     edge[r][c+1][0] = False
#     result.remove([r, c, 0])
#     return
#
#
# def delete_beam(edge, result, r, c):
#     if [r, c, 1] not in result:
#         return
#
#     if ([r+1, c, 0] in result) and ([r+1, c, 1] not in result) and ([r+1, c-1, 0] not in result):
#         return
#     elif ([r, c, 0] in result) and ([r-1, c, 1] not in result) and ([r, c-1, 0] not in result):
#         return
#     elif ([r-1, c, 1] in result) and ([r, c-1, 0] not in result) and ([r-1, c-1, 0] not in result):
#         return
#     elif ([r+1, c, 1] in result) and ([r+1, c-1, 0] not in result) and ([r+2, c-1, 0] not in result):
#         return
#
#     edge[r][c][1] = False
#     edge[r+1][c][1] = False
#     if [r-1, c, 1] in result:
#         edge[r][c][1] = True
#     if [r+1, c, 1] in result:
#         edge[r+1][c][1] = True
#     result.remove([r, c, 1])
#     return


build_frame = [[1,0,0,1],[1,1,1,1],[2,1,0,1],[2,2,1,1],[5,0,0,1],[5,1,0,1],[4,2,1,1],[3,2,1,1]]

print(solution(5, build_frame))