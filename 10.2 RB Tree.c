#include <stdio.h>
#include <stdlib.h>

struct node {
    int d; 
    int c; // 1-red, 0-black
    struct node* p; // parent
    struct node* r; // right-child
    struct node* l; // left child
};

struct node* root = NULL;// global root

struct node* bst(struct node* root, struct node* temp)// function to perform BST insertion of a node
{
    if (root == NULL)// If the tree is empty, return a new node
        return temp;

    if (temp->d < root->d) // Otherwise recur down the tree
    {
        root->l = bst(root->l, temp);
        root->l->p = root;
    }
    else if (temp->d > root->d) 
    {
        root->r = bst(root->r, temp);
        root->r->p = root;
    }

    return root;// Return the (unchanged) node pointer
}

// Function performing right rotation of the passed node
void rightrotate(struct node* temp)
{
    struct node* left = temp->l;
    temp->l = left->r;
    if (temp->l)
        temp->l->p = temp;
    left->p = temp->p;
    if (!temp->p)
        root = left;
    else if (temp == temp->p->l)
        temp->p->l = left;
    else
        temp->p->r = left;
    left->r = temp;
    temp->p = left;
}

// Function performing left rotation of the passed node
void leftrotate(struct node* temp)
{
    struct node* right = temp->r;
    temp->r = right->l;
    if (temp->r)
        temp->r->p = temp;
    right->p = temp->p;
    if (!temp->p)
        root = right;
    else if (temp == temp->p->l)
        temp->p->l = right;
    else
        temp->p->r = right;
    right->l = temp;
    temp->p = right;
}

void fixup(struct node* root, struct node* node)// This function fixes violations caused by BST insertion
{
    struct node* parent_node = NULL;
    struct node* grand_parent_node = NULL;

    while((node!=root) && (node->c==1) && (node->p->c==1))// nodes of not root, node is red, parent color is red 
    {
        parent_node = node->p;
        grand_parent_node = node->p->p;

        // Case:'A' Parent of the node is left child of Grand-parent of the node 
        if (parent_node==grand_parent_node->l) 
        {
            struct node* uncle_node = grand_parent_node->r;
            //Case:1 The uncle of node is also red, only Recoloring required 
            if (uncle_node != NULL && uncle_node->c == 1) 
            {
                grand_parent_node->c = 1;
                parent_node->c = 0;
                uncle_node->c = 0;
                node=grand_parent_node;
            }
            else 
            {
                // Case:2 node is right child of its parent, Left-rotation required
                if (node==parent_node->r) 
                {
                    leftrotate(parent_node);
                    node = parent_node;
                    parent_node = node->p;
                }
                // caused:3 node is left child of its parent Right-rotation required 
                rightrotate(grand_parent_node);
                int t = parent_node->c;
                parent_node->c = grand_parent_node->c;
                grand_parent_node->c = t;
                node = parent_node;
            }
        }

        // Case:B Parent of node is right child of Grand-parent of node 
        else {
            struct node* uncle_node = grand_parent_node->l;

            // Case:1 The uncle of node is also red only Recoloring required 
            if((uncle_node != NULL) && (uncle_node->c == 1)) 
            {
                grand_parent_node->c = 1;
                parent_node->c = 0;
                uncle_node->c = 0;
                node = grand_parent_node;
            }
            else 
            {
                //Case:2 node is left child of its parent Right-rotation required 
                if (node == parent_node->l) 
                {
                    rightrotate(parent_node);
                    node = parent_node;
                    parent_node = node->p;
                }

                // Case:3 node is right child of its parent Left-rotation required 
                leftrotate(grand_parent_node);
                int t = parent_node->c;
                parent_node->c = grand_parent_node->c;
                grand_parent_node->c = t;
                node = parent_node;
            }
        }
    }
}
//-------------------------delete----------------------------
// Leftmost node of a subtree (successor helper)
// Since NULL is used for leaves (no sentinel), x's parent is tracked
// explicitly as x_parent, because x itself may be NULL here.
struct node* minimum(struct node* node)
{
    while (node->l != NULL)
        node = node->l;
    return node;
}
 
// Replace subtree rooted at u with subtree rooted at v
void transplant(struct node* u, struct node* v)
{
    if (u->p == NULL)
        root = v;
    else if (u == u->p->l)
        u->p->l = v;
    else
        u->p->r = v;
    if (v != NULL)
        v->p = u->p;
}
 
// x may be NULL (no sentinel), so its parent is tracked explicitly as xp.
// left/right cases are mirror images, collapsed here via the `side` flag:
// side=1 means x is a left child (sibling on the right), side=0 the reverse.
void deletefixup(struct node* x, struct node* xp)
{
    while (x != root && (x == NULL || x->c == 0))
    {
        int side = (x == xp->l);
        struct node* w = side ? xp->r : xp->l;          // sibling
        struct node* near = side ? w->l : w->r;         // nephew next to x
        struct node* far  = side ? w->r : w->l;          // nephew away from x
 
        if (w->c == 1) // Case 1: red sibling -> rotate to get a black one
        {
            w->c = 0;
            xp->c = 1;
            side ? leftrotate(xp) : rightrotate(xp);
            w = side ? xp->r : xp->l;
            near = side ? w->l : w->r;
            far  = side ? w->r : w->l;
        }
        if ((near == NULL || near->c == 0) && (far == NULL || far->c == 0))
        {
            // Case 2: both nephews black -> recolor, push violation up
            w->c = 1;
            x = xp;
            xp = x->p;
        }
        else
        {
            if (far == NULL || far->c == 0) // Case 3: near nephew red -> rotate onto far side
            {
                if (near != NULL) near->c = 0;
                w->c = 1;
                side ? rightrotate(w) : leftrotate(w);
                w = side ? xp->r : xp->l;
            }
            // Case 4: far nephew red -> rotate at xp, done
            w->c = xp->c;
            xp->c = 0;
            far = side ? w->r : w->l;
            if (far != NULL) far->c = 0;
            side ? leftrotate(xp) : rightrotate(xp);
            x = root;
            xp = NULL;
        }
    }
    if (x != NULL)
        x->c = 0;
}

// Deletes node z from the tree and rebalances if a black node was removed
void deletenode(struct node* z)
{
    struct node* y = z;
    struct node *x, *xp;
    int y_color = y->c;
 
    if (z->l == NULL || z->r == NULL)
    {
        x = z->l ? z->l : z->r;
        xp = z->p;
        transplant(z, x);
    }
    else
    {
        y = minimum(z->r); // in-order successor
        y_color = y->c;
        x = y->r;
        xp = (y->p == z) ? y : y->p;
 
        if (y->p != z)
        {
            transplant(y, y->r);
            y->r = z->r;
            y->r->p = y;
        }
        transplant(z, y);
        y->l = z->l;
        y->l->p = y;
        y->c = z->c;
    }
    free(z);
    if (y_color == 0) // black node removed -> fix double-black
        deletefixup(x, xp);
}
 
// BST search, needed to locate the node to delete by key
struct node* search(struct node* root, int key)
{
    if (root == NULL || root->d == key)
        return root;
    if (key < root->d)
        return search(root->l, key);
    return search(root->r, key);
}
 
void deletekey(int key)
{
    struct node* z = search(root, key);
    if (z == NULL)
    {
        printf("Key %d not found, nothing deleted\n", key);
        return;
    }
    deletenode(z);
}

void inorder(struct node* trav)
{
    if (trav == NULL)
        return;
    inorder(trav->l);
    printf("%d ", trav->d);
    inorder(trav->r);
}

int main()
{
    int n=8;
    int a[8]={10, 20, 30, 15, 25, 5, 1, 40};
    for(int i=0; i<n; i++) 
    {
        struct node* temp=(struct node*)malloc(sizeof(struct node));
        temp->r=NULL;
        temp->l=NULL;
        temp->p=NULL;
        temp->d=a[i];
        temp->c=1;// color as red
        root = bst(root, temp);//performs bst insertion

        fixup(root, temp);//function to preserve properties of rb tree
          root->c=0;
    }
    printf("Inorder Traversal of Created Tree\n");
    inorder(root);
    return 0;
}