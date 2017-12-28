#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct noop
{
    char name[100];
    char num[12];
    struct noop *next;
};

typedef struct noop noop;

struct saleDay
{
    int a;
    int b;
    int c;
};
typedef struct saleDay saleDay;

int menu()
{
    printf("1.Doc File danhsach.txt\n2.Them Nguoi Mua\n3.Ban Hang\n4.Ghi thong tin sau 1 ngay\n5.Thong Ke thong tin ban hang\n6.Yeu Cau Dac Biet\n7.Thoat\n");
    char s[10];
    scanf("%[^\n]%*c", s);
    int c = (int)atoi(s);
    return c;
}

struct noop * makeNoop()
{
    noop * temp = (noop *)malloc(sizeof(noop));
    temp->next =NULL;
    return temp;
}

void showQueue(noop *top)
{
    if (top!=NULL)
    {
        while (top!=NULL)
        {
            printf("%s\t%s\n", top->name, top->num);
            top=top->next;
        }
    }
}

void enQueue(noop ** top, noop ** rear, noop ** temp)
{
    if (*top == NULL)
    {
        *top= *temp;
        *rear= *temp;
    }
    else 
    {
        (*rear)->next = *temp;
        (*rear) = *temp;
    }
}

struct noop* deQueue(noop ** top, noop ** rear)
{    
    if (*top==NULL) return *top;
    else
    {
        noop * temp; //= makeNoop(); 
        temp =*top;
        *top = (*top)->next;
        return temp;
    }
}

int putQueue(noop ** top, noop ** rear)
{
    FILE *f;
    f = fopen("danhsach.txt", "w+");
    if (top==NULL) printf("NOBODY\n");
    else
    {
        while (1)
        {
            noop * del = deQueue(top,rear);
            if (del!=NULL) fprintf(f,"%s\t%s\n", del->name, del->num);
            else break;
        }
    }
    fclose(f);
    return 1;
}

int docFile(char *file, noop ** top, noop ** rear)
{
    FILE *f;
    f = fopen(file, "r");
    if (f==NULL) {perror("LOI:"); return 1;} 
    while (1)
    {
        noop * temp = makeNoop();
        char text[112];
        if (fscanf(f, "%[^\n]%*c", text)==EOF) break;
        sscanf(text, "%s\t%s", temp->name, temp->num);
        enQueue(top,rear,&temp);
    }
    fclose(f);

    printf("_DS:\n");
    showQueue(*top);
    return 0;
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

int themKH(noop ** top, noop ** rear)
{
    noop * temp = makeNoop();
    char text[100];
    do {
    printf("_Ten:");
    scanf("%[^\n]%*c", text);   
    } while (haveSpace(text));
    strcpy(temp->name, text);
    printf("_SDT:");
    scanf("%s%*c", temp->num);

    enQueue(top, rear, &temp);
    return 1;
}

int banHang(noop ** top, noop ** rear)
{
    noop * del = deQueue(top, rear);
    if (del ==NULL) return 0;
    FILE *f;
    f = fopen("banhang.txt", "a+");
    printf("#A:_");
    int a;
    do {
        printf("\t");
        scanf("%d%*c", &a);
    } while (a<0);

    printf("#B:_");
    int b;
    do {
        printf("\t");
        scanf("%d%*c", &b);
    } while (b<0);

    printf("#C:_");
    int c;
    do {
        printf("\t");
        scanf("%d%*c", &c);
    } while (c<0);

    fprintf(f,"%d %d %d\n", a, b, c);
    fclose(f);
}

int hetNgay(noop ** top, noop ** rear)
{
    printf("_QUEUE inDAY:\n");
    showQueue(*top);

    putQueue(top,rear);

    FILE *f;
    f= fopen("banhang.txt", "a+");
    fprintf(f,"-1\n");
    fclose(f);
    return 0;
}

int thongKe()
{
    saleDay day[90];
    int i =-1;
    FILE *f;
    f = fopen("banhang.txt", "r");
    if (f==NULL) {perror("LOI"); return 1;}

    while (1)
    {
        i++;
        int end=0;
        day[i].a = 0;
        day[i].b = 0;
        day[i].c = 0;
        while (1)
        {
            char text[100];
            if (fscanf(f, "%[^\n]%*c", text) == EOF) {end =1; break;}   text[strlen(text)-1]='\0';
            int d = (int)atoi(text);
            //printf("%s", text);
            if (d==-1) break;
            int a,b,c;
            sscanf(text, "%d %d %d", &a,&b,&c);
            day[i].a = day[i].a +a;
            day[i].b = day[i].b +b;
            day[i].c = day[i].c +c;
        };
        if (end ==1) break;
    }
    fclose(f);

    int j;
    printf("%5s %5s %5s\n", "_A","_B", "_C");
    for (j=0; j<i; j++)
    {
        printf("%5d %5d %5d\n", day[j].a, day[j].b, day[j].c);
    }
    return 0;
}

int boChauLamTo(noop ** top, noop ** rear, noop ** temp)
{
    if (top==NULL)
    {
        *rear = *temp;
        *top = *temp;
    }
    else    
    {
        (*temp)->next = *top;
        *top = *temp;
    }
}

int coCau(noop ** top, noop ** rear)
{
    noop * temp= makeNoop();

    char text[100];
    do {
    printf("_Ten:");
    scanf("%[^\n]%*c", text);   
    } while (haveSpace(text));
    strcpy(temp->name, text);

    printf("_SDT:");
    scanf("%s%*c", temp->num);

    boChauLamTo(top, rear, &temp);
}

int main()
{
    noop * khach=NULL; noop * rearKhach=NULL;
    int c;
    while (c!=7)
    {
        c = menu();
        switch (c)
        {
            case 1: docFile("danhsach.txt", &khach, &rearKhach);
            break;
            case 2: themKH(&khach, &rearKhach);
            break;
            case 3: banHang(&khach, &rearKhach);
            break;
            case 4: hetNgay(&khach, &rearKhach);
            break;
            case 5: thongKe();
            break;
            case 6: coCau(&khach, &rearKhach);
            break;
        }
    }
    return 0;
}