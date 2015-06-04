#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void my_menu();
void my_read();
void my_write();
void my_delete();
void my_edit();
void my_add();


typedef struct {
    int num;
    char name[30];
    char klas[2];
    int marks[64];
    float avr;
}st;


int main()
{
    my_menu();
}
void my_menu()
{
    system("CLS");
    int op=1, cuop;
    char c=0;
    while(c != 13)
    {
        if(op == 1) printf("> 1.Write\n");
        else printf("  1.Write\n");
        if(op == 2) printf("> 2.Read\n");
        else printf("  2.Read\n");
        if(op == 3) printf("> 3.Edit\n");
        else printf("  3.Edit\n");
        if(op == 4) printf("> 4.Add\n");
        else printf("  4.Add\n");
        if(op == 5) printf("> 5.Delete\n");
        else printf("  5.Delete\n");
        if(op == 6) printf("> 6.Exit\n");
        else printf("  6.Exit\n");
        c = getch();
        system("CLS");
        if(c==80)
        {
            if(op<6) op++;
            else op = 1;
        }
        if (c==72)
        {
            if(op>1) op--;
            else op = 6;
        }
        if (c == 13)
        {
            switch(op)
            {
                case 1: my_write(); break;
                case 2: my_read(); break;
                case 3: my_edit(); break;
                case 4: my_add(); break;
                case 5: my_delete(); break;
                case 6: break;
            }
        }
    }
}
void my_write()
{
    FILE *f;
    st s;
    int j;
    f = fopen("9v.dat","w");///Trie vsichko i zapochva da pishe na novo
    if(f)
    {
        while(1)
        {
            s.avr=0;
            printf("Number:");
            scanf("%d",&s.num);
            if(s.num==0) break;
            printf("\nName:");
            gets(s.name);
            gets(s.name);
            for(j=0;1;j++)
            {
                printf("\nGrade No %d:",j+1);
                scanf("%d",&s.marks[j]);
                if(s.marks[j]==0) break;
                s.avr+=s.marks[j];
            }
            s.avr/=j;
            fwrite(&s,sizeof(s),1,f);
        }
        fclose(f);
    }
    system("pause");
    my_menu();
}
void my_read()
{
    FILE *f;
    st s;
    int i=0;
    f = fopen("9v.dat","r");
    if(f)
    {
        while(!feof(f))
        {
            if(fread(&s,sizeof(s),1,f))
            {
                printf("\nNum:%d \nName: %s",s.num,s.name);
                i=0;
                while(s.marks[i])
                {
                    printf("\nMarks: %d",s.marks[i]);
                    i++;
                }
                printf("\nAvr:%.2f",s.avr);
            }
        }
        fclose(f);
    }

    system("pause");
    my_menu();
}
void my_add()
{
    FILE *f;
    st s;
    f = fopen("9v.dat","r+");
    int j;
    if(f)
    {
        while(!feof(f)) fread(&s,sizeof(s),1,f);
        while(1)
        {
            printf("Number:");
            scanf("%d",&s.num);
            if(s.num==0) break;
            printf("\nName:");
            gets(s.name);
            gets(s.name);
            for(j=0;1;j++)
            {
                printf("\nGrade No %d:",j+1);
                scanf("%d",&s.marks[j]);
                if(s.marks[j]==0) break;
                s.avr+=s.marks[j];
            }
            s.avr/=j;
            fwrite(&s,sizeof(s),1,f);
        }
        fclose(f);
    }
    system("pause");
    my_menu();

}
void my_delete()
{
    FILE *f_9v;
    FILE *f_tp;
    st s;
    int num_delete;
    scanf("%d",&num_delete);
    f_tp = fopen("temp.dat","w");
    f_9v = fopen("9v.dat","r");
    while(!feof(f_9v))
    {
        if(fread(&s,sizeof(s),1,f_9v))
            if(num_delete!=s.num)
                fwrite(&s,sizeof(s),1,f_tp);
    }
    fclose(f_9v);
    fclose(f_tp);
    f_9v = fopen("9v.dat","w");
    f_tp = fopen("temp.dat","r");
    while(!feof(f_tp))
    {
        fread(&s,sizeof(s),1,f_tp);
        fwrite(&s,sizeof(s),1,f_9v);
    }
    fclose(f_9v);
    fclose(f_tp);
    my_menu();
}
void my_edit()
{
    FILE *f_9v;
    FILE *f_tp;
    st s;
    int num_edit,j;
    scanf("%d",&num_edit);
    f_tp = fopen("temp.dat","w");
    f_9v = fopen("9v.dat","r");
    while(!feof(f_9v))
    {
        if(fread(&s,sizeof(s),1,f_9v))
        {
            if(num_edit!=s.num)
                fwrite(&s,sizeof(s),1,f_tp);
            else
            {
                printf("Number:");
                scanf("%d",&s.num);
                if(s.num==0) break;
                printf("\nName:");
                gets(s.name);
                gets(s.name);
                s.avr=0;
                for(j=0;1;j++)
                {
                    printf("\nGrade No %d:",j+1);
                    scanf("%d",&s.marks[j]);
                    if(s.marks[j]==0) break;
                    s.avr+=s.marks[j];
                }
                s.avr/=j;
                fwrite(&s,sizeof(s),1,f_tp);
            }
        }

    }
    fclose(f_9v);
    fclose(f_tp);
    f_9v = fopen("9v.dat","w");
    f_tp = fopen("temp.dat","r");
    while(!feof(f_tp))
    {
        if(fread(&s,sizeof(s),1,f_tp))
            fwrite(&s,sizeof(s),1,f_9v);
    }
    fclose(f_9v);
    fclose(f_tp);

    system("pause");
    my_menu();
}
