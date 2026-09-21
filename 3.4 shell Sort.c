#include <stdio.h>

void shellSort(int arr[], int n) 
{
    for (int gap=n/2; gap>0; gap/=2) 
    {
        for (int i=gap; i<n; i++) 
        {
            int temp=arr[i];
            int j=i;
            
            while (j>=gap && arr[j-gap]>temp) 
            {
                arr[j]=arr[j-gap];
                j-=gap;
            }
            arr[j]=temp;
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

    shellSort(arr,n);
        
    for(int i=0; i<n; i++)
        printf("%d ",arr[i]);

    return 0;
}