#include<stdio.h>

int partition(int arr[],int left, int right)
{
    int pivot=arr[right];
    int i=left;
    int j=right;
    while(i<j)
    {
        while(i<=right && arr[i]<=pivot)
            i++;

        while(j>=left && arr[j]>pivot)
            j--;

        if(i<j)
        {
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }
    int temp=arr[left];
    arr[left]=arr[j];
    arr[j]=temp;
    return j;
}

void quickSort(int arr[], int left,int right)
{
    if(left<right)
    {
        int pivot=partition(arr,left,right);
        quickSort(arr,left,pivot-1);
        quicksort(arr,pivot+1,right);
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

    quickSort(arr,0,n-1);
        
    for(int i=0; i<n; i++)
        printf("%d ",arr[i]);

    return 0;
}