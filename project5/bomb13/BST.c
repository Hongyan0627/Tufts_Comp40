#include <stdlib.h>
#include <stdio.h>

struct node {
        const char *person;
        const char *footwear;
        struct node *left, *right;
};
typedef struct node *Tree;

static struct node nh = {
        "Hescott",
        "loafer",
        NULL,
        NULL
};

static struct node nb = {
        "Brodley",
        "aboot",
        NULL,
        NULL
};

static struct node nr = {
        "Ramsey",
        "Birkenstock",
        &nh,
        &nb
};

int postOrder(Tree root);

int main() 
{
        int sum;
        
        sum = postOrder(&nr);
        printf("the number of nodes is: %d\n", sum);
        
        return 0;
}

int postOrder(Tree root)
{
        int sum = 1;
        
        if (root == NULL)
                return 0;
        
        if (root->left != NULL)
                sum = sum + postOrder(root->left);
        
        if (root->right != NULL)
                sum = sum + postOrder(root->right);
        
        return sum;
}
