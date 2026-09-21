#include<stdio.h>
#include <limits.h>

int main()
{
    int n;
    printf("n = ");
    scanf("%d",&n);
    int a[n],b[n],k=INT_MIN;
    for(int i=0;i<n;i++)
    {
        scanf("%d",a[i]);
        if(k<a[i])
            k=a[i];
    }
    
    int c[k+1];
    for(int i=0;i<=k;i++)
        c[i]=0;

    for(int i=0;i<n;i++)
        c[a[i]]++;

    for(int i=1;i<=k;i++)
        c[i]+=c[i-1];

    for(int i=n-1;i>=0;i--)
    {
        b[c[a[i]]-1]=a[i];
        c[a[i]]--;
    }

    for(int i=0;i<n;i++)
        printf("%d ",b[i]);

    return 0;
}