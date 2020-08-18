import re

arr1 = re.findall('\d+',input())
arr1 = list(map(int,arr1))
N = arr1[0]
K = arr1[1]

arr = re.findall('\d+',input())
arr = list(map(int,arr))
concept = []
def hasindex(list1, new):
    list2 = []
    for i in list1:
        list2.append(i)
    n1 = len(list(set(list2)))
    list2.append(new)
    if n1 == len(list(set(list2))):
        return True
    else:
        return False

def multitap(index):
    global arr
    global concept
    #이미 가지고 있는지 판단
    if hasindex(concept,arr[index]):
        return 0
    #여유공간이 있는지 판단
    if len(set(concept)) < N:
        concept.append(arr[index])
        return 0

    temp_arr = []
    for i in range(index,len(arr)):
        temp_arr.append(arr[i])
    #앞으로 쓸일 없을 콘셉트 제거
    for i in concept:
        if hasindex(temp_arr,i) == False:
            concept.remove(i)
            concept.append(arr[index])
            return 1
    #가장 나중에 쓸거 하나 제거 한후 추가
    a = []
    for i in range(N):
        a.append(0)
    for i in range(N):
        for j in range(len(temp_arr)):
            if concept[i] == temp_arr[j]:
                a[i] = j
                break
    a_max = a[0]
    for i in range(len(a)):
        if a[i] > a_max:
            a_max = a[i]

    concept.remove(temp_arr[a_max])
    concept.append(arr[index])
    return 1

result = 0
for i in range(len(arr)):
    result += multitap(i)


print(result)





