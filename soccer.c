#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct noob
{
    int id;
    char name[30];
    int point;
    int win;
    int lose;
    struct noob *next;
};


typedef struct noob noob;


int menu()
{
    printf("_MENU:\n");
    printf("1.Cac doi bong\n2.Lich Thi Dau\n3.Cap nhat ket qua\n4.Thong Ke\n5.Thoat\n_");
    char s[10];
    scanf("%[^\n]", s);
    if (s[0]=='\0') s[0]='0';
    else scanf("%*c");
    int c = (int)atoi(s);
    return c;
}

struct noob * makeNoob(int id, char *name)
{
    noob * temp = (noob*)malloc(sizeof(noob));
    temp->next=NULL;
    /////////////////
    temp->id = id;
    strcpy(temp->name, name);
    temp->point = 0;
    temp->win = 0;
    temp->lose = 0;
    return temp;
}

void addTop(noob ** list, noob ** new) // hay la PUSH() trong STACK
{
    (*new)->next = *list;
    *list = *new;
}

void showList(noob * list)
{
    if (list != NULL)
    {
        printf("%3d%30s%3d%7d%10d\n", list->id, list->name, list->point, list->win, list->lose);
        showList(list->next);
    }
}

struct noob * searchNoob(noob * list, int id)
{
    if (list == NULL) return NULL;
    else if (list->id == id) return list;
    else return searchNoob(list->next, id);
}

int rFile(char *file, noob ** list)
{
    FILE *f;
    f = fopen(file, "r");
    if (f==NULL) {perror("LOI"); return 1;}
    int N,i;
    fscanf(f,"%d%*c", &N);
    for (i=0; i<N; i++)
    {
        //////// doc mot dong trong file
        char line[100];
        if (fscanf(f, "%[^\n]%*c", line) == EOF) break;
        
        ///////////////////////////// doc cau truc cua 1 dong
        int id;
        char name[30];
        sscanf(line, "%d\t%[^\n]", &id, name);
        
        /////////////////////// dua vao cay
        noob *new = makeNoob(id, name);
        addTop(list, &new); // 
    }

    showList(*list);
    return 1;
}

int lichThiDau(char *file, noob * list)
{
    FILE *f;
    f = fopen(file, "r");
    if (f==NULL) {perror("LOI"); return 1;}
    int N,i;
    fscanf(f,"%d%*c", &N);
    for (i=0; i<N; i++)
    {
        char line[100];
        if (fscanf(f, "%[^\n]%*c", line) == EOF) break; 
    }

    int j;
    for (j=0; j<N-1; j++)
    {
        char line[30];
        fscanf(f, "%[^\n]%*c", line);
        printf("Vong %d\n",j+1);
        int k;
        for (k=0; k<N/2; k++)
        {
            int t1, t2;
            fscanf(f, "%d\t%d\n", &t1, &t2);
            noob * team1 = searchNoob(list, t1);
            noob * team2 = searchNoob(list, t2);
            if ((team1!=NULL)&&(team2!=NULL)) printf("%s - %s\n", team1->name, team2->name);
        }
    }

    fclose(f);
    return 0;
}

void tiSo(noob ** team1, noob ** team2)
{
    printf("Ti So: \n");
    int t1, t2;
    scanf("%d%*c", &t1);
    scanf("%d%*c", &t2);
    (*team1)->win += t1;
    (*team1)->lose += t2;
    (*team2)->win += t2;
    (*team2)->lose += t1;

    if (t1== t2) 
    {
        (*team1)->point ++;
        (*team2)->point ++;
    }
    else if (t1 > t2)
    {
        (*team1)->point +=3;
    }
    else
    {
        (*team2)->point +=3;
    }
}

int capNhat(char *file, noob * list, int vong)
{
    FILE *f;
    f = fopen(file, "r");
    if (f==NULL) {perror("LOI"); return 1;}
    int N,i;
    fscanf(f,"%d%*c", &N);
    for (i=0; i<N; i++)
    {
        char line[100];
        if (fscanf(f, "%[^\n]%*c", line) == EOF) break; 
    }

    int j;
    for (j=0; j<N-1; j++)
    {
        char line[30];
        fscanf(f, "%[^\n]%*c", line);
        if (vong == j) printf("%s\n",line);
        int k;
        for (k=0; k<N/2; k++)
        {
            int t1, t2;
            fscanf(f, "%d\t%d\n", &t1, &t2);

            if (vong == j) 
            {
                noob * team1 = searchNoob(list, t1);
                noob * team2 = searchNoob(list, t2);
                if ((team1!=NULL)&&(team2!=NULL)) printf("%s - %s: ", team1->name, team2->name);

                tiSo(&team1, &team2);
            }
        }
    }

    fclose(f);
    return 0;
}

int thongke(noob *list)
{
    printf("%3s%30s %s %s %s\n\n", "ID", "Ten", "Diem", "SobanThang", "SobanThua");
    showList(list);
}

int main()
{
    noob * list =NULL;
    int c;
    int vong = 0;
    while (c!=5)
    {
        c = menu();
        switch (c)
        {
            case 1: rFile("bongda.txt", &list);
            break;       
            case 2: lichThiDau("bongda.txt", list);
            break; 
            case 3: capNhat("bongda.txt", list, vong);
                    vong++; 
            break;    
            case 4: thongke(list);
            break; 
        }
    }
    return 1;
}
