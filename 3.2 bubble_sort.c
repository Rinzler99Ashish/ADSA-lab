#include<stdio.h>

void bubbleSort(int arr[], int n)
{
    for (int i=0; i<n-1; i++)
    {  
        int f=0;
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                f=1;
            }
        }
        if(f==0)
            break;
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

    bubbleSort(arr,n);
        
    for(int i=0; i<n; i++)
        printf("%d ",arr[i]);

    return 0;
}