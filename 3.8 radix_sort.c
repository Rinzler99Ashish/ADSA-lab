#include<stdio.h>

int give_max(int arr[],int n)
{
    int max=arr[0];
    for(int i=1;i<n;i++)
        if(max<arr[i])
            max=arr[i];
    
    return max;
}

int give_min(int arr[],int n)
{
    int min=arr[0];
    for(int i=1;i<n;i++)
        if(min>arr[i])
            min=arr[i];
    
    return min;
}

void sort(int arr[],int n,int exp)
{
    int process[10][n];
    int count[10],b[n],k=0;
    for(int i=0;i<10;i++)
        count[i]=0;

    for(int i=0;i<n;i++)
        process[(arr[i]/exp)%10][count[(arr[i]/exp)%10]++]=arr[i];

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<count[i];j++)
        {
            b[k++]=process[i][j];
        }
    }

    for(int i=0;i<n;i++)
        arr[i]=b[i];    
}

void radix_sort(int arr[],int n)
{
    int max=give_max(arr,n);
    int min=give_min(arr,n);
    
    // If there are negative numbers, shift all numbers by adding absolute value of min
    if(min < 0)
    {
        int shift = -min;
        for(int i=0;i<n;i++)
            arr[i] += shift;
        max = give_max(arr,n);
    }

    for(int exp=1;(max/exp)>0;exp*=10)
        sort(arr,n,exp);
    
    // Shift back if we shifted earlier
    if(min < 0)
    {
        int shift = -min;
        for(int i=0;i<n;i++)
            arr[i] -= shift;
    }
}

int main()
{
    printf("Enter n = ");
    int n;    
    scanf("%d",&n);
    printf("Enter elements: ");
    int arr[n];
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);

    radix_sort(arr,n);

    printf("Sorted Array: ");
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);

    return 0;
}