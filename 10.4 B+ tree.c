#include <stdio.h>
#include <stdlib.h>

int T; /* min degree = max_degree/2 */

typedef struct N {
    int leaf, n, *k;
    struct N **c, *nx;
} N;

N *root = NULL;

N* mk(int leaf){
    N*x=malloc(sizeof(N)); x->leaf=leaf; x->n=0;
    x->k=malloc(sizeof(int)*(2*T));
    x->c=malloc(sizeof(N*)*(2*T+1));
    x->nx=NULL; return x;
}

void freeTree(N*x){
    if(!x) return;
    if(!x->leaf) for(int i=0;i<=x->n;i++) freeTree(x->c[i]);
    free(x->k); free(x->c); free(x);
}

int has(N*x,int k){
    if(!x) return 0;
    while(!x->leaf){ int i=0; while(i<x->n&&k>=x->k[i])i++; x=x->c[i]; }
    for(int i=0;i<x->n;i++) if(x->k[i]==k) return 1;
    return 0;
}

void splitChild(N*x,int i){
    N*y=x->c[i],*z=mk(y->leaf); int j,sep;
    if(y->leaf){
        for(j=0;j<T;j++) z->k[j]=y->k[T-1+j];
        z->n=T; y->n=T-1; z->nx=y->nx; y->nx=z; sep=z->k[0];
    } else {
        for(j=0;j<T-1;j++) z->k[j]=y->k[T+j];
        for(j=0;j<T;j++) z->c[j]=y->c[T+j];
        z->n=y->n=T-1; sep=y->k[T-1];
    }
    for(j=x->n;j>i;j--){ x->k[j]=x->k[j-1]; x->c[j+1]=x->c[j]; }
    x->k[i]=sep; x->c[i+1]=z; x->n++;
}

void insNF(N*x,int k){
    int i=x->n-1;
    if(x->leaf){
        while(i>=0&&k<x->k[i]){ x->k[i+1]=x->k[i]; i--; }
        x->k[i+1]=k; x->n++;
    } else {
        while(i>=0&&k<x->k[i]) i--; i++;
        if(x->c[i]->n==2*T-1){ splitChild(x,i); if(k>=x->k[i]) i++; }
        insNF(x->c[i],k);
    }
}

void insert(int k){
    if(has(root,k)) return;
    if(!root){ root=mk(1); root->k[0]=k; root->n=1; return; }
    if(root->n==2*T-1){ N*s=mk(0); s->c[0]=root; splitChild(s,0); root=s; }
    insNF(root,k);
}

void borrowL(N*x,int i){
    N*c=x->c[i],*l=x->c[i-1];
    if(c->leaf){
        for(int j=c->n;j>0;j--) c->k[j]=c->k[j-1];
        c->k[0]=l->k[l->n-1]; c->n++; l->n--; x->k[i-1]=c->k[0];
    } else {
        for(int j=c->n;j>0;j--) c->k[j]=c->k[j-1];
        for(int j=c->n+1;j>0;j--) c->c[j]=c->c[j-1];
        c->k[0]=x->k[i-1]; c->c[0]=l->c[l->n]; c->n++;
        x->k[i-1]=l->k[l->n-1]; l->n--;
    }
}

void borrowR(N*x,int i){
    N*c=x->c[i],*r=x->c[i+1];
    if(c->leaf){
        c->k[c->n]=r->k[0]; c->n++;
        for(int j=0;j<r->n-1;j++) r->k[j]=r->k[j+1];
        r->n--; x->k[i]=r->k[0];
    } else {
        c->k[c->n]=x->k[i]; c->c[c->n+1]=r->c[0]; c->n++;
        x->k[i]=r->k[0];
        for(int j=0;j<r->n-1;j++) r->k[j]=r->k[j+1];
        for(int j=0;j<r->n;j++) r->c[j]=r->c[j+1];
        r->n--;
    }
}

void merge(N*x,int i){
    N*a=x->c[i],*b=x->c[i+1];
    if(a->leaf){
        for(int j=0;j<b->n;j++) a->k[a->n+j]=b->k[j];
        a->n+=b->n; a->nx=b->nx;
    } else {
        a->k[a->n]=x->k[i];
        for(int j=0;j<b->n;j++) a->k[a->n+1+j]=b->k[j];
        for(int j=0;j<=b->n;j++) a->c[a->n+1+j]=b->c[j];
        a->n+=b->n+1;
    }
    for(int j=i;j<x->n-1;j++){ x->k[j]=x->k[j+1]; x->c[j+1]=x->c[j+2]; }
    x->n--; free(b->k); free(b->c); free(b);
}

void fill(N*x,int i){
    if(i>0&&x->c[i-1]->n>T-1) borrowL(x,i);
    else if(i<x->n&&x->c[i+1]->n>T-1) borrowR(x,i);
    else { if(i>0) merge(x,i-1); else merge(x,i); }
}

void delR(N*x,int k){
    int i=0;
    while(i<x->n&&k>=x->k[i]) i++;
    if(x->leaf){
        int j=0; while(j<x->n&&x->k[j]<k) j++;
        if(j<x->n&&x->k[j]==k){
            for(int t=j;t<x->n-1;t++) x->k[t]=x->k[t+1];
            x->n--;
        }
        return;
    }
    if(x->c[i]->n==T-1){ fill(x,i); i=0; while(i<x->n&&k>=x->k[i]) i++; }
    delR(x->c[i],k);
}

void del(int k){
    if(!has(root,k)) return;
    delR(root,k);
    if(root&&!root->leaf&&root->n==0){
        N*o=root; root=root->c[0];
        free(o->k); free(o->c); free(o);
    } else if(root&&root->leaf&&root->n==0){
        free(root->k); free(root->c); free(root); root=NULL;
    }
}

void prt(){
    if(!root){ printf("(empty)\n"); return; }
    N*x=root; while(!x->leaf) x=x->c[0];
    printf("Keys: ");
    for(;x;x=x->nx) for(int i=0;i<x->n;i++) printf("%d ",x->k[i]);
    printf("\n");
}

int main(){
    int md;
    printf("Max degree (even >=4): ");
    if(scanf("%d",&md)!=1||md<4||md%2) md=6;
    T=md/2;
    int c,k,n;
    while(1){
        printf("\n1.Create 2.Insert 3.Delete 4.Free 5.Exit\n> ");
        if(scanf("%d",&c)!=1) break;
        if(c==1){
            printf("n: "); scanf("%d",&n);
            printf("%d keys: ",n);
            while(n--){ scanf("%d",&k); insert(k); }
            prt();
        } else if(c==2){ printf("k: "); scanf("%d",&k); insert(k); prt(); }
        else if(c==3){ printf("k: "); scanf("%d",&k); del(k); prt(); }
        else if(c==4){ freeTree(root); root=NULL; printf("freed\n"); }
        else if(c==5){ freeTree(root); return 0; }
    }
    freeTree(root); return 0;
}