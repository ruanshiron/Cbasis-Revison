#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct noob 
{
    int data;
    struct noob * left;
    struct noob * right;
}

typedef noob nood;

struct noob * makeNoob()
{
    noob * temp = (noob *)malloc(sizeof noob);
    temp->data = 0;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
} 

void addLeaf(noob ** tree, noob ** temp)
{
    if (tree == NULL)
    {
        tree = temp;
    }
    else if (tree->data > temp->data)   addLeaf(&((*tree)->left), temp);
    else    addLeaf(&((*tree)->right), temp);
}

void showTree(noob * tree)
{
    if (tree!=NULL)
    {
        showTree(tree->left);
        showTree(tree->right);
    }
}

int main()
{
    return 0;
}