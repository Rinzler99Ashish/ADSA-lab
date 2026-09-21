#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}

struct Node *LL(struct Node *y)//rightRotate is used to fix an LL imbalance.
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),height(y->right))+1;
    x->height = max(height(x->left),height(x->right))+1;

    return x;
}

struct Node *RR(struct Node *x)//leftRotate is used to fix an RR imbalance.
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left)-height(N->right);
}

struct Node* insert(struct Node* node, int key)
{
    if (node == NULL)
        return(newNode(key));

    if(key < node->key)
        node->left =insert(node->left, key);
    else if(key > node->key)
        node->right = insert(node->right, key);
    else 
        return node;// Equal keys are not allowed in BST

    node->height=1 + max(height(node->left),height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)// Left Left Case
        return LL(node);
    if (balance < -1 && key > node->right->key)// Right Right Case
        return RR(node);
    if (balance > 1 && key > node->left->key)// Left Right Case
    {
        node->left =  RR(node->left);
        return LL(node);
    }
    if (balance < -1 && key < node->right->key)// Right Left Case
    {
        node->right = LL(node->right);
        return RR(node);
    }
    return node;
}

struct Node * minValueNode(struct Node* node) 
{
     struct Node* current = node;

    // loop down to find the leftmost leaf
    while (current->left != NULL)
        current = current->left;

    return current;
}

struct Node* deleteNode(struct Node* root, int key) 
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else 
    {
        if ((root->left == NULL) || (root->right == NULL)) 
        {
            struct Node *temp = root->left ? root->left : root->right;
            if (temp != NULL) // One child case
            {
                free(root);
                return temp; 
            }
            else//No child case
            {
                free(root);
                root=NULL;
            }
        } 
        else// node with two children:
        {
            struct Node* temp = minValueNode(root->right);// Get the inorder successor 
            root->key = temp->key;// Copy the inorder successor's data to this node
            root->right = deleteNode(root->right, temp->key); // Delete the inorder successor
        }
    }
    
    if (root==NULL)// If the tree had only one node then return
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return LL(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = RR(root->left);
        return LL(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return RR(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = LL(root->right);
        return RR(root);
    }

    return root;
}

void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    struct Node *root = NULL;

  /* Constructing tree given in the above figure */
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    printf("Preorder traversal of the  constructed AVL tree is \n");
    preOrder(root);

    root = deleteNode(root, 10);

    printf("Preorder traversal after deletion of 10\n");
    
    preOrder(root);

    return 0;
}