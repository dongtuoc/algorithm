#! /usr/bin/python3

l = [1,99,2,98,44,22,66,21,9,12,45,22,44]

def insertsort(L):
    '''
    @插入排序 时间复杂度O(n2) 空间复杂度O(1)
    '''
    for i in range(1,len(L)):
        j = i - 1
        key = L[i]
        
        while(j >= 0 and key < L[j]):
            L[j+1] = L[j]
            j-=1
        L[j+1] = key
    return L

if __name__ == "__main__":
    print("l before:",l)
    insertsort(l)
    print("l after:",l)
    
    
    
