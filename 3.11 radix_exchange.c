#include <stdio.h>
#include <limits.h>

void radixSort(int arr[], int left, int right, unsigned int bit) 
{
    if(left>=right || bit==0)  
        return;
    
    int i=left, j=right;
    
    while (i<=j) 
    {
        while (i<=j && !((unsigned int)(arr[i]^INT_MIN) & bit)) 
            i++;
        while (i<=j && ((unsigned int)(arr[j]^INT_MIN) & bit)) 
            j--;
        if(i<j) 
        {
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
            i++; 
            j--;
        }
    }
    radixSort(arr, left, j, bit>>1);
    radixSort(arr, i, right, bit>>1);
}

void sort(int arr[], int n) 
{
    radixSort(arr, 0, n-1, (unsigned int)INT_MIN);
}

int main()
{
    int n;
    printf("Enter n = ");
    scanf("%d",&n);

    int arr[n];
    for(int i=0; i<n; i++)
        scanf("%d",&arr[i]);

    sort(arr, n);
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}