#include <stdio.h>
#include <stdlib.h>

int min(int a,int b)
{
    if(a>b)return b;
    return a;
}

void mergeSort(int* first,int* last)
{
    if(first >= last) {return;}
    int len = last-first+1;
    int mid = len/2;
    mergeSort(first,first+mid-1);
    mergeSort(first+mid,last);
    int* pom = malloc(sizeof(int)*len);
    int* iter1 = first;
    int* iter2 = first+mid;
    int* miditer = iter2;
    int l = 0;
    while(iter1 < miditer && iter2 <= last)
    {
        int nxt = min(*iter1,*iter2);
        if(nxt==*iter1)iter1++;
        else iter2++;
        pom[l++]=nxt;
    }
    while(iter1 < miditer)pom[l++]=*iter1++;
    while(iter2 <= last)pom[l++]=*iter2++;
    for(int i = 0; i < len; i++)
    {
        *(first+i)=pom[i];
    }
    free(pom);
}


int main() {
    int a[] = {1,5,4,6,6,9,2,10,4,-2,-13,999999};
    int n = sizeof(a)/sizeof(a[0]);
    mergeSort(a,a+n-1);
    for(int i = 0; i < n; i++)
    {
        printf("%d ",*(a+i));
    }
    return 0;
}
