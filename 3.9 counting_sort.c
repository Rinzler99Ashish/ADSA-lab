#include<stdio.h>
#include <limits.h>

void counting_sort(int arr[],int n)
{
    // Find minimum and maximum
    int min = arr[0], max = arr[0];
    for(int i=1;i<n;i++) {
        if(arr[i] < min) min = arr[i];
        if(arr[i] > max) max = arr[i];
    }
    
    // Shift range to handle negative numbers
    int range = max - min + 1;
    int c[range], b[n];

    for(int i=0;i<range;i++)
        c[i]=0;

    // Store count with shift
    for(int i=0;i<n;i++)
        c[arr[i] - min] += 1;

    for(int i=1;i<range;i++)
        c[i] += c[i-1];

    for(int i=n-1;i>=0;i--)
    {
        b[c[arr[i] - min] - 1] = arr[i];
        c[arr[i] - min] -= 1;
    }
    
    for(int i = 0; i < n; i++)
        arr[i]=b[i];
}

int main()
{
    int n;
    printf("n = ");
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);
    
    counting_sort(arr,n);

    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);

    return 0;
}