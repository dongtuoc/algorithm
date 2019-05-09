#!/usr/bin/python3


l = [1,99,2,98,44,22,66,21,9,12,45,22,44]

def selectsort(L):
    '''
    @选择排序:时间复杂度O(n2) 空间复杂度O(1)
    '''
    for i in range(0,len(L)-1):
        index = i
        for j in range(i+1,len(L)):
            if L[index] > L[j]:
                index = j
        L[i],L[index] = L[index],L[i]
    return L

if __name__ == "__main__":
    print("l before:",l)
    selectsort(l)
    print("l after:",l)
     
