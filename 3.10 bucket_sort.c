#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void insertionSort(float arr[], int n)
{
    for(int i=1; i<n; i++)
    {
        float key = arr[i];
        int j=i-1;
        while (j>=0 && arr[j]>key)
        {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(float A[], int n)
{
    float B[n][MAX];
    int count[n];
    for (int i = 0; i < n; i++)
        count[i] = 0;

    for (int i = 0; i < n; i++)// Insert A[i] into bucket[n * A[i]]
    {
        int index = (int)(n * A[i]);
        B[index][count[index]] = A[i];
        count[index]++;
    }

    for(int i = 0; i < n; i++)
        insertionSort(B[i], count[i]);

    int k=0;
    for(int i=0; i<n; i++)// Concatenate all buckets
        for (int j=0; j<count[i]; j++)
            A[k++]=B[i][j];
}

int main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    float A[n];
    printf("Enter elements (0 <= x < 1):\n");
    for (int i = 0; i < n; i++)
        scanf("%f", &A[i]);

    bucketSort(A, n);
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%.2f ", A[i]);

    return 0;
}