#include<stdio.h>

void merge(int arr[],int left, int mid, int right)
{
    int i=left;
    int j=mid+1;
    int w=0,b[right-left+1];
    while(i<=mid && j<=right)
    {
        if(arr[i]<arr[j])
            b[w++]=arr[i++];
        else
            b[w++]=arr[j++];
    }
    while(i<=mid)
        b[w++]=arr[i++];
    while(j<=right)
        b[w++]=arr[j++];

    for(int i=0;i<w;i++)
        arr[left+i]=b[i];
}

void mergeSort(int arr[], int left,int right)
{
    if(left<right)
    {
        int mid=(left+right)/2;
        mergeSort(arr,left,mid);
        mergeSort(arr,mid+1,right);
        merge(arr,left,mid,right);
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

    mergeSort(arr,0,n-1);
        
    for(int i=0; i<n; i++)
        printf("%d ",arr[i]);

    return 0;
}