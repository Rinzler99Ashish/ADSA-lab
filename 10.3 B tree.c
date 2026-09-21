/*
 * B-tree implementation.
 * This version only adds indentation and explanatory comments.
 * The original code logic is unchanged.
 */

#include <stdio.h>
#include <stdlib.h>

/* B-tree node: keys, number of keys, leaf flag, children */
typedef struct N {
    int *k, n, leaf;
    struct N **c;
} N;

/* Minimum degree of the B-tree */
int T;

/* Create a new node. leaf = 1 for a leaf node, 0 otherwise. */
N* mk(int leaf) {
    N* x = malloc(sizeof(N));
    x->k = malloc((2*T-1)*sizeof(int));
    x->c = malloc(2*T*sizeof(N*));
    x->n = 0;
    x->leaf = leaf;
    return x;
}

/* Recursively free the whole tree. */
void rm(N* x) {
    if (!x) return;
    if (!x->leaf) for (int i = 0; i <= x->n; i++) rm(x->c[i]);
    free(x->k); free(x->c); free(x);
}

/* Search for key k in the subtree rooted at x. */
N* find(N* x, int k) {
    int i = 0;
    while (i < x->n && k > x->k[i]) i++;
    if (i < x->n && x->k[i] == k) return x;
    return x->leaf ? NULL : find(x->c[i], k);
}

/* Split child x->c[i] into two nodes. */
void split(N* x, int i) {
    N *y = x->c[i], *z = mk(y->leaf);
    int mid = y->k[T-1];

    for (int j = 0; j < T-1; j++) z->k[j] = y->k[j+T];
    if (!y->leaf) for (int j = 0; j < T; j++) z->c[j] = y->c[j+T];

    y->n = z->n = T-1;

    for (int j = x->n; j >= i+1; j--) x->c[j+1] = x->c[j];
    x->c[i+1] = z;

    for (int j = x->n-1; j >= i; j--) x->k[j+1] = x->k[j];
    x->k[i] = mid;
    x->n++;
}

/* Insert key k into a non-full node x. */
void insNf(N* x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->k[i]) {
            x->k[i+1] = x->k[i];
            i--;
        }
        x->k[i+1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->k[i]) i--;
        i++;

        if (x->c[i]->n == 2*T-1) {
            split(x, i);
            if (k > x->k[i]) i++;
        }

        insNf(x->c[i], k);
    }
}

/* Find predecessor key for x->k[i]. */
int pred(N* x, int i) {
    N* c = x->c[i];
    while (!c->leaf) c = c->c[c->n];
    return c->k[c->n-1];
}

/* Find successor key for x->k[i]. */
int succ(N* x, int i) {
    N* c = x->c[i+1];
    while (!c->leaf) c = c->c[0];
    return c->k[0];
}

/* Borrow a key from the previous sibling. */
void borP(N* x, int i) {
    N *c = x->c[i], *s = x->c[i-1];

    for (int j = c->n-1; j >= 0; j--) c->k[j+1] = c->k[j];
    c->k[0] = x->k[i-1];

    if (!c->leaf) {
        for (int j = c->n; j >= 0; j--) c->c[j+1] = c->c[j];
        c->c[0] = s->c[s->n];
    }

    x->k[i-1] = s->k[s->n-1];
    s->n--;
    c->n++;
}

/* Borrow a key from the next sibling. */
void borN(N* x, int i) {
    N *c = x->c[i], *s = x->c[i+1];

    c->k[c->n] = x->k[i];
    if (!c->leaf) c->c[c->n+1] = s->c[0];

    x->k[i] = s->k[0];

    for (int j = 1; j < s->n; j++) s->k[j-1] = s->k[j];
    if (!s->leaf) for (int j = 1; j <= s->n; j++) s->c[j-1] = s->c[j];

    c->n++;
    s->n--;
}

/* Merge child i and child i+1. */
void mrg(N* x, int i) {
    N *y = x->c[i], *z = x->c[i+1];

    y->k[y->n] = x->k[i];
    for (int j = 0; j < z->n; j++) y->k[y->n+1+j] = z->k[j];
    if (!y->leaf) for (int j = 0; j <= z->n; j++) y->c[y->n+1+j] = z->c[j];

    y->n += z->n + 1;

    for (int j = i; j < x->n-1; j++) x->k[j] = x->k[j+1];
    for (int j = i+1; j < x->n; j++) x->c[j] = x->c[j+1];
    x->n--;

    free(z->k);
    free(z->c);
    free(z);
}

/* Ensure child i has enough keys before deletion. */
void fill(N* x, int i) {
    if (i > 0 && x->c[i-1]->n >= T)       borP(x, i);
    else if (i < x->n && x->c[i+1]->n >= T) borN(x, i);
    else if (i < x->n)                      mrg(x, i);
    else                                    mrg(x, i-1);
}

/* Delete key k from the subtree rooted at x. */
void del(N* x, int k) {
    int i = 0;
    while (i < x->n && k > x->k[i]) i++;

    if (i < x->n && x->k[i] == k) {
        if (x->leaf) {
            for (int j = i; j < x->n-1; j++) x->k[j] = x->k[j+1];
            x->n--;
        } else if (x->c[i]->n >= T) {
            int p = pred(x, i);
            x->k[i] = p;
            del(x->c[i], p);
        } else if (x->c[i+1]->n >= T) {
            int s = succ(x, i);
            x->k[i] = s;
            del(x->c[i+1], s);
        } else {
            mrg(x, i);
            del(x->c[i], k);
        }
    } else {
        if (x->leaf) return;

        int last = (i == x->n);
        if (x->c[i]->n < T) fill(x, i);
        del(x->c[last && i > x->n ? i-1 : i], k);
    }
}

/* Root of the B-tree */
N* root = NULL;

/* Insert key k into the B-tree. */
void insert(int k) {
    if (!root) {
        root = mk(1);
        root->k[0] = k;
        root->n = 1;
        return;
    }

    if (root->n == 2*T-1) {
        N* s = mk(0);
        s->c[0] = root;
        split(s, 0);
        root = s;
    }

    insNf(root, k);
}

/* Delete key k from the B-tree. */
void delItem(int k) {
    if (!root) return;

    del(root, k);

    if (root->n == 0) {
        N* o = root;
        root = o->leaf ? NULL : o->c[0];
        free(o->k);
        free(o->c);
        free(o);
    }
}

/* Print the tree level by level with indentation. */
void print(N* x, int lv) {
    if (!x) return;

    for (int i = 0; i < lv; i++) printf("  ");
    for (int i = 0; i < x->n; i++) printf("%d ", x->k[i]);
    printf("\n");

    if (!x->leaf) for (int i = 0; i <= x->n; i++) print(x->c[i], lv+1);
}

/* Menu-driven main program. */
int main() {
    printf("t: ");
    scanf("%d", &T);
    if (T < 2) T = 2;

    int ch, k, n;

    while (printf("\n1. Create from sequence\n2. Insert\n3. Delete\n4. Delete tree\n5. Print\n6. Exit\n >" ), scanf("%d", &ch), ch != 6) {

        if (ch == 1) {
            rm(root);
            root = NULL;

            printf("n: ");
            scanf("%d", &n);
            printf("keys: ");

            for (int i = 0; i < n; i++) {
                scanf("%d", &k);
                insert(k);
            }
        }
        else if (ch == 2) {
            printf("k: ");
            scanf("%d", &k);
            insert(k);
        }
        else if (ch == 3) {
            printf("k: ");
            scanf("%d", &k);
            delItem(k);
        }
        else if (ch == 4) {
            rm(root);
            root = NULL;
        }
        else if (ch == 5) {
            print(root, 0);
        }
    }

    rm(root);
    return 0;
}