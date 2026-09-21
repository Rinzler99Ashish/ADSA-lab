#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int lo, int mid, int hi) 
{
    int n1 = mid-lo +1,n2=hi-mid, i=0, j=0, k=lo;
    int *L = malloc(n1*sizeof(int));
    int *R = malloc(n2*sizeof(int));

    for (int a = 0; a<n1; a++) 
        L[a] = arr[lo+a];
    for (int b=0; b<n2; b++) 
        R[b] = arr[mid+1+b];

    while (i<n1 && j<n2) 
        arr[k++]=(L[i]<=R[j]) ? L[i++] : R[j++];
    while (i < n1) 
        arr[k++] = L[i++];
    while (j < n2) 
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSortBottomUp(int arr[], int n) 
{
    for(int width=1; width<n; width*=2) 
    {
        for(int lo=0; lo<n; lo+=2*width) 
        {
            int mid= (lo+width-1 < n-1) ? lo+width-1 : n-1;
            int hi= (lo+2*width-1 < n-1)? lo+2*width-1 : n-1;

            if(mid<hi) 
                merge(arr, lo, mid, hi);
        }
    }
}

int main()
{
    int n;
    printf("Enter n = ");
    scanf("%d",&n);

    int arr[n];
    for(int i=0; i<n; i++)
        scanf("%d",&arr[i]);

    mergeSortBottomUp(arr, n);
        
    for(int i=0; i<n; i++)
        printf("%d ",arr[i]);

    return 0;
}