#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct noob 
{
    int id;
    char name[30];
    struct noob * left;
    struct noob *right;
};

typedef struct noob noob;

int menu()
{
    printf("1.Doc File A\n2.Doc File B\n3.\n4.\n5.\n6.\n");
    char s[10];
    scanf("%[^\n]%*c", s);
    int c = (int)atoi(s);
    return c;
}

struct noob * makeNoob()
{
    noob * temp = (noob *)malloc(sizeof(noob));
    temp->left = NULL;
    temp->right = NULL;
    return temp;
} 

void addLeaf(noob ** tree, noob ** temp)
{
    if (*tree == NULL)
    {
        *tree = *temp;
    }
    else if ((*tree)->id > (*temp)->id)   addLeaf(&(*tree)->left, temp);
    else    addLeaf(&(*tree)->right, temp);
}

void showTree(noob * tree)
{
    if (tree!=NULL)
    {
        showTree(tree->left);
        printf("%d %s\n", tree->id, tree->name);
        showTree(tree->right);
    }
}

int docFile(char c, noob ** A)
{
    FILE *f;
    if (c=='A') f = fopen("A.txt", "r");
    if (c=='B') f = fopen("B.txt", "r");
    
    if (f==NULL) {perror("LOI"); return 1;}

    int i=0;
    noob * noInfo[100];
    while (1)
    {
        noob * link = makeNoob();
        char text[100];
        if (fscanf(f, "%[^\n]%*c",text)==EOF) break;

        sscanf(text, "%d\t%s", &link->id, link->name);
        if (link->name[0]=='\0') 
        {
            noInfo[i]=link;
            i++;
        }
        addLeaf(A, &link);
    }
    int j;

    printf("_DS:\n");
    showTree(*A);

    printf("_Thieu thong tin qua: \n");
    for (j=0; j<i;j++)
    {
        printf("%d Nhap ten qua:", noInfo[j]->id);
        scanf("%s%*c", noInfo[j]->name);
    }

    printf("_DS:\n");
    showTree(*A);

    fclose(f);
    return 0;
}

void delLeaf(noob ** tree, noob ** node)
{
    noob * link = makeNoob();
    link->left = (*node)->left;
    link->right = (*node)->right;
    link->id = (*node)->id;
    strcpy(link->name, (*node)->name);
    *node = NULL;

    addLeaf(tree,&link->left);
    addLeaf(tree,&link->right);
}
void compareB(noob ** As,noob ** A, noob ** B)
{
    if (*A!=NULL)
    {
        if ((*B)->id == (*A)->id) delLeaf(As,A);
        compareB(As,&(*A)->left, B);
        compareB(As,&(*A)->right, B);
    }
}

void detectA(noob ** As, noob ** A, noob ** B)
{
    if (*B!=NULL)
    {
        compareB(As,A, B);
        detectA(As,A, &(*B)->left);
        detectA(As,A, &(*B)->right);
    }
}

int timKiem(noob ** A, noob ** B)
{
    detectA(A,A,B);
    showTree(*A);
}


int main()
{
    noob *A=NULL;
    noob *B=NULL;
    int c;
    while (c!=6)
    {
        c = menu();
        switch (c)
        {
            case 1: docFile('A',&A);
            break;
            case 2: docFile('B',&B);
            break;
            case 3: timKiem(&A,&B);
            break;
            case 4: //tongHop();
            break;
            case 5: //thongKe();
            break;
        }
    }
    return 0;
}