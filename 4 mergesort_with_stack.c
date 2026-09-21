#include <stdio.h>

typedef struct { int l, r; } Range;

void merge(int arr[], int l, int m, int r) {
    int n1=m-l+1, n2=r-m;
    int L[n1], R[n2];
    for(int i=0;i<n1;i++) L[i]=arr[l+i];
    for(int j=0;j<n2;j++) R[j]=arr[m+1+j];
    int i=0,j=0,k=l;
    while(i<n1 && j<n2) arr[k++] = (L[i]<=R[j]) ? L[i++] : R[j++];
    while(i<n1) arr[k++]=L[i++];
    while(j<n2) arr[k++]=R[j++];
}

void mergeSortStack(int arr[], int n) {
    Range stk[100], order[100];
    int top=-1, cnt=0;
    stk[++top] = (Range){0, n-1};

    while(top>=0) {
        Range cur = stk[top--];
        if(cur.l < cur.r) {
            int m = cur.l + (cur.r-cur.l)/2;
            order[cnt++] = cur;
            stk[++top] = (Range){cur.l, m};
            stk[++top] = (Range){m+1, cur.r};
        }
    }
    for(int i=cnt-1; i>=0; i--) {
        int m = order[i].l + (order[i].r-order[i].l)/2;
        merge(arr, order[i].l, m, order[i].r);
    }
}

int main() {
    int arr[] = {6,3,5,2,4,1};
    int n = sizeof(arr)/sizeof(arr[0]);
    mergeSortStack(arr, n);
    for(int i=0;i<n;i++) printf("%d ", arr[i]);
    return 0;
}