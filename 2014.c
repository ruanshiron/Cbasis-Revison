#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct noop 
{
    char username[30];
    char password[30];
    float mark;
    struct noop * left;
    struct noop * right;
};

typedef struct noop noop;

int menu()
{
    printf("1.Dang Nhap\n2.Thoat\n");
    char s[10];
    scanf("%[^\n]%*c", s);
    int c = (int)atoi(s);
    return c;
}

struct noop * makeNoop()
{
    noop * temp = (noop *)malloc(sizeof(noop));
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void addNoop(noop ** tree, noop ** temp)
{
    if (*tree == NULL)
    {
        *tree = *temp;
    }
    else if (strcmp((*tree)->username, (*temp)->username)>0)   addNoop(&(*tree)->left, temp);
    else    addNoop(&(*tree)->right, temp);
}

void showNoop(noop * tree)
{
    if (tree!=NULL)
    {
        showNoop(tree->left);
        printf("%s\t%s\t%f\n", tree->username, tree->password, tree->mark);
        showNoop(tree->right);
    }
}

void putNoop(FILE *f, noop * tree)
{
    if (tree!=NULL)
    {
        putNoop(f,tree->left);
        fprintf(f,"%s\t%s\t%f\n", tree->username, tree->password, tree->mark);
        putNoop(f,tree->right);
    }
}

struct noop * Bsearch(noop * tree, char *username, char *password)
{
    if (tree == NULL) return NULL;
    if ((strcmp(username, tree->username) == 0) && (strcmp(password, tree->password) == 0)) return tree;
    else if (strcmp(tree->username, username)>0) return Bsearch(tree->left, username, password);
    else return Bsearch(tree->right, username, password);
}

int docDuLieu(char *file, noop ** user)
{
    FILE *f;
    f = fopen(file, "r");
    if (f==NULL) {perror("LOI"); return 1;}
    while (1)
    {
        char line[100];
        if (fscanf(f,"%[^\n]%*c", line) == EOF) break;

        noop * temp = makeNoop();
        sscanf(line, "%s\t%s\t%f", temp->username, temp->password, &temp->mark);

        addNoop(user, &temp);
    }
    fclose(f);
    //showNoop(*user);
    return 1;
}

int ghiLenFile(char *file, noop ** user)
{
    FILE *f;
    f = fopen(file, "w+");
    putNoop(f, *user);
    fclose(f);
}

int haveSpace(char *s)
{
    int i=0;
    while (s[i]!='\0')
    {
        if (s[i]==' ') return 1;
        i++;
    }
    //printf("%s,\n",s);
    return 0;
}

int isAdmin(noop * tree, char *username, char *password, noop ** nowUser)
{
    if (strcmp(username, "Admin")==0) 
    {
        *nowUser = Bsearch(tree,"Admin", password);
        if (*nowUser==NULL) return 0;
        else return 1;
    }
    else return 0;
}

int isUser(noop * tree, char *username, char *password, noop ** nowUser)
{
    *nowUser = Bsearch(tree, username, password);
    if (*nowUser==NULL) return 0;
    else return 1;
}

int login(noop * tree, noop ** nowUser)
{
    
    int error=0;

    do
    {
        if (error == 3) return 2;
        char username[30];
        char password[30];
        do{
            printf("_Username:");
            scanf("%[^\n]%*c",username);
        } while(haveSpace(username));

        do {
            printf("_Password:");
            scanf("%[^\n]%*c",password);
        } while(strlen(password)<6);

        if (isAdmin(tree, username, password, nowUser)) return -1;
        //if (isUser(tree, username, password, nowUser)) return -2;
        error++;
    } while (1);

}

int Amenu()
{
    printf("1. Them User\n2. Danh Sach User\n3. Xoa User\n4. Luu va Thoat\n");
    char s[10];
    scanf("%[^\n]%*c", s);
    int c = (int)atoi(s);
    return c;
}

int themUser(noop ** user)
{
    noop * temp = makeNoop();
    do{
        printf("_Username:");
        scanf("%[^\n]%*c",temp->username);
    } while(haveSpace(temp->username));

    do {
        printf("_Password:");
        scanf("%[^\n]%*c",temp->password);
    } while(strlen(temp->password)<6);

    addNoop(user, &temp);
    return 1;
}

void showUser(noop * tree)
{
    if (tree!=NULL)
    {
        if (strcmp(tree->username, "Admin")!=0) 
        {
            showNoop(tree->left);
            printf("%s\t%s\t%f\n", tree->username, tree->password, tree->mark);
            showNoop(tree->right);
        }
        else 
        {
            showNoop(tree->left);
            showNoop(tree->right);
        }
    }
}

int DSuser(noop ** user)
{
    showUser(*user);
    return 1;
}

struct noop * BUsearch(noop * tree, char *username)
{
    if ((strcmp(username, tree->username) == 0)) return tree;
    else if (strcmp(tree->username, username)>0) return BUsearch(tree->left, username);
    else return BUsearch(tree->right, username);
}

void delNoop(noop ** user, noop ** del)
{
    noop * link = makeNoop();
    link->left = (*del)->left;
    link->right = (*del)->right;
    strcpy(link->password, (*del)->password);
    strcpy(link->username, (*del)->username);
    link->mark = (*del)->mark;
    *del = NULL;

    if (link->left != NULL) addNoop(user, &link->left);
    if (link->right != NULL) addNoop(user, &link->right);
}

int xoaUser(noop ** user)
{
    char username[30];
    do{
        printf("_DELusername:");
        scanf("%[^\n]%*c",username);
    } while(haveSpace(username));

    noop * del= BUsearch(*user, username);
    if (del == NULL) printf("KHONG TON TAI!\n");
    else delNoop(user, &del);
    return 1;
}

int adminMenu(noop ** user)
{
    printf("-1_ADMIN: \n");
    int c;
    
    while (c!=4)
    {
        c = Amenu();
        switch (c)
        {
            case 1: themUser(user);
            break;
            case 2: DSuser(user);
            break;
            case 3: xoaUser(user);
            break;
        }
    }

    ghiLenFile("sinhvien.txt",user);    

    return 1;
}

int Umenu()
{
    printf("1. Xem diem\n2. Doi Mat Khau\n3. Luu va Thoat\n");
    char s[10];
    scanf("%[^\n]%*c", s);
    int c = (int)atoi(s);
    return c;
}

int xemDiem(noop * user)
{
    printf("_Mark:%f\n", user->username, user->mark);
    return 1;
}

int doiMatKhau(noop ** user)
{
    char password[30];
    char Rpassword[30];
    while (1)
    {
        do {
            printf("_newPass:");
            scanf("%[^\n]%*c",password);
        } while(strlen(password)<6);

        printf("_REnewPass:");
        scanf("%[^\n]%*c",Rpassword);

        if (strcmp(password, Rpassword)==0) break;
    }

    strcpy((*user)->password, password);
    return 1;
}

int userMenu(noop ** nowUser, noop ** user)
{
    printf("-2_%s:\n", (*nowUser)->username);
    int c;
    
    while (c!=3)
    {
        c = Umenu();
        switch (c)
        {
            case 1: xemDiem(*nowUser);
            break;
            case 2: doiMatKhau(nowUser);
            break;
        }
    }

    ghiLenFile("sinhvien.txt",user);
    return 1;
}

int main()
{
    int c;
    noop * User = NULL;
    noop * nowUser = NULL;
    docDuLieu("sinhvien.txt", &User);

    while (c!=2)
    {
        c = menu();
        switch (c)
        {
            case 1: c = login(User, &nowUser);
                    switch (c)
                    {
                        case -1: adminMenu(&User);
                        break;
                        case -2: userMenu(&nowUser, &User);
                        break;
                    };
            break;
        }
        nowUser = NULL;
    }
    return 0;
}