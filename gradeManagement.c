#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
void menu();
void in();
void show(int n);
void search();
void del();
void modify();
void insert();
void order();
void total();
struct student
{
    char name[20];
    int num;
    double elec;
    double expe;
    double requ;
    double sum;
}stu[100];
int LEN=sizeof(struct student);
char *FORMAT="%1d\t\t%-10s\t\t%2.1f\t\t%2.1f\t\t%2.1f\t\t%2.1f\n";
char* TOP="number\t\tname\t\t\telective\texperiment\trequired\tsum\n";
float lelec,lexpe,lrequ;
int main()
{
    int n;
    menu();
    scanf("%d",&n);
    while(n){
        switch(n){
            case 1:
                in();
                break;
            case 2:
                search();
                break;
            case 3:
                del();
                break;
            case 4:
                modify();
                break;
            case 5:
                insert();
                break;
            case 6:
                order();
                break;
            case 7:
                total();
                break;
            default:
                break;
        }
        getch();
        menu();
        scanf("%d",&n);
    }
}
void menu(){
    system("cls");
    printf("\n\n\n\n\n");
    printf("\t\t|---------------------STUDENT---------------------|\n");
    printf("\t\t|\t 0. exit                                  |\n");
    printf("\t\t|\t 1. input record                          |\n");
    printf("\t\t|\t 2. search record                         |\n");
    printf("\t\t|\t 3. delete record                         |\n");
    printf("\t\t|\t 4. modify record                         |\n");
    printf("\t\t|\t 5. insert record                         |\n");
    printf("\t\t|\t 6. order                                 |\n");
    printf("\t\t|\t 7. number                                |\n");
    printf("\t\t|-------------------------------------------------|\n\n");
    printf("\t\t\tchoose(0-7):");
}
void in(){
    int i,m=0;
    char ch[2];
    FILE *fp;
    if((fp=fopen("data","ab+"))==NULL){
        printf("cannot open\n");
        return;
    }
    while(!feof(fp)){
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
    }
    fclose(fp);
    if(m==0)
        printf("No record!\n");
    else{
        system("cls");
        show(m);
    }
    if((fp=fopen("data","wb"))==NULL){
        printf("cannot open\n");
        return;
    }
    for(i=0;i<m;i++)
        fwrite(&stu[i],LEN,1,fp);
    printf("please input(y/n):");
    scanf("%s",ch);
    if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0){
        printf("please input per centum:");
        printf("\nelective:");
        scanf("%f",&lelec);
        printf("\nexperiment:");
        scanf("%f",&lexpe);
        printf("\nrequired course:");
        scanf("%f",&lrequ);
    }
    while(strcmp(ch,"Y")==0||strcmp(ch,"y")==0){
        printf("number:");
        scanf("%d",&stu[m].num);
        for(i=0;i<m;i++)
            if(stu[i].num==stu[m].num){
                printf("the number is existing, press any to continue!");
                getch();
                fclose(fp);
                return;
            }
        printf("name:");
        scanf("%s",stu[m].name);
        printf("elective:");
        scanf("%lf",&stu[m].elec);
        printf("experiment:");
        scanf("%lf",&stu[m].expe);
        printf("required course:");
        scanf("%lf",&stu[m].requ);
        stu[m].sum=stu[m].elec*lelec+stu[m].expe*lexpe+stu[m].requ*lrequ;
        if(fwrite(&stu[m],LEN,1,fp)!=1){
            printf("cannot save!");
            getch();
        }else
        {
            printf("%s saved!\n",stu[m].name);
            m++;
        }
        printf("continun?(y/n):");
        scanf("%s",ch);
    }
    fclose(fp);
    printf("OK!\n");
}
void show(int n){
    int i;
    printf(TOP);
    for(i=0;i<n;i++)
        printf(FORMAT,stu[i].num,stu[i].name,stu[i].elec,stu[i].expe,stu[i].requ,stu[i].sum);
}
void search(){
    FILE *fp;
    int snum,i,m=0;
    char ch[2];
    if((fp=fopen("data","ab+"))==NULL){
        printf("cannot open\n");
        return;
    }
    while(!feof(fp))
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
    fclose(fp);
    if(m==0){
        printf("no record!\n");
        return;
    }
    printf("please input the number:");
    scanf("%d",&snum);
    for(i=0;i<m;i++)
        if(snum==stu[i].num){
            printf("find the student,show?(y/n)");
            scanf("%s",ch);
            if(strcmp(ch,"Y")==0||strcmp(ch,"y")==0){
                printf(TOP);
                printf(FORMAT,stu[i].num,stu[i].name,stu[i].elec,stu[i].expe,stu[i].requ,stu[i].sum);
            }
            break;
        }
    if(i==m)
        printf("cannot find the student!\n");
}
void del(){
    FILE *fp;
    int snum,i,j,m=0;
    char ch[2];
    if((fp=fopen("data","ab+"))==NULL){
        printf("cannot open\n");
        return;
    }
    while(!feof(fp))
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
    fclose(fp);
    if(m==0){
        printf("no record!\n");
        return;
    }
    printf("please input the number:");
    scanf("%d",&snum);
    for(i=0;i<m;i++)
        if(snum==stu[i].num)
            break;
    if(i==m){
        printf("cannot find student!");
        return;
    }
    printf("find the student, delete?(y/n)");
    scanf("%s",ch);
    if(strcmp("Y",ch)==0||strcmp("y",ch)==0){
        for(j=i;j<m;j++)
            stu[j]=stu[j+1];
        m--;
    }
    if((fp=fopen("data","wb"))==NULL){
        printf("cannot open\n");
        return;
    }
    for(j=0;j<m;j++)
        if(fwrite(&stu[j],LEN,1,fp)!=1){
            printf("cannot save!\n");
            getch();
        }
    fclose(fp);
    printf("delete successfully!\n");
}
void modify(){
    FILE *fp;
    int i,j,m=0,snum;
    if((fp=fopen("data","ab+"))==NULL){
        printf("cannot open\n");
        return;
    }
    while(!feof(fp))
        if(fread(&stu[m],LEN,1,fp))
            m++;
    if(m==0){
        printf("no record!\n");
        fclose(fp);
        return;
    }
    printf("please input the number of the student whick do you want to modify!\n");
    scanf("%d",&snum);
    for(i=0;i<m;i++)
        if(snum==stu[i].num)
            break;
    if(i<m){
        printf("find the student! You can modify!\n");
        printf("please input per centum:");
        printf("\nelective:");
        scanf("%f",&lelec);
        printf("\nexperiment:");
        scanf("%f",&lexpe);
        printf("\nrequired course:");
        scanf("%f",&lrequ);
        printf("name:\n");
        scanf("%s",stu[i].name);
        printf("\nelective:");
        scanf("%lf",&stu[i].elec);
        printf("\nexperiment:");
        scanf("%lf",&stu[i].expe);
        printf("\nrequired course:");
        scanf("%lf",&stu[i].requ);
        stu[i].sum=stu[i].elec*lelec+stu[i].expe*lexpe+stu[i].requ*lrequ;
    }else{
        printf("cannot find!");
        getchar();
        return;
    }
    if((fp=fopen("data","wb"))==NULL){
        printf("cannot open\n");
        return;
    }
    for(j=0;j<m;j++)
        if(fwrite(&stu[j],LEN,1,fp)!=1){
            printf("cannot save!");
            return;
        }
    fclose(fp);
}
void insert(){
    FILE *fp;
    int i,j,k,m=0,snum;
    if((fp=fopen("data","ab+"))==NULL){
        printf("cannot open\n");
        return;
    }
    while(!feof(fp))
        if(fread(&stu[m],LEN,1,fp)==1)
            m++;
    if(m==0){
        printf("no record!\n");
        fclose(fp);
        return;
    }
    printf("please input position where do you want to insert!(input the student number)\n");
    scanf("%d",&snum);
    for(i=0;i<m;i++)
        if(snum==stu[i].num)
            break;
    if(i!=m)
        for(j=m-1;j>i;j--)
            stu[j+1]=stu[j];
    else
    {
        i--;
    }
    
    printf("now please input the new information.\n");
    printf("number:");
    scanf("%d",&stu[i+1].num);
    m++;
    for(k=0;k<m;k++)
        if(stu[k].num==stu[i+1].num&&k!=i+1){
            printf("the number is existing, press any to continue!");
            getch();
            fclose(fp);
            return;
        }
    printf("please input per centum:");
    printf("\nelective:");
    scanf("%f",&lelec);
    printf("\nexperiment:");
    scanf("%f",&lexpe);
    printf("\nrequired course:");
    scanf("%f",&lrequ);
    printf("name:\n");
    scanf("%s",stu[i+1].name);
    printf("\nelective:");
    scanf("%lf",&stu[i+1].elec);
    printf("\nexperiment:");
    scanf("%lf",&stu[i+1].expe);
    printf("\nrequired course:");
    scanf("%lf",&stu[i+1].requ);
    stu[i+1].sum=stu[i+1].elec*lelec+stu[i+1].expe*lexpe+stu[i+1].requ*lrequ;
    if((fp=fopen("data","wb"))==NULL){
        printf("cannot open\n");
        return;
    }
    for(k=0;k<=m;k++)
        if(fwrite(&stu[k],LEN,1,fp)!=1){
            printf("cannot save!");
            getch();
        }
    fclose(fp);
}
void order(){
    FILE *fp;
    int i,j,m=0;
    struct student stemp;
    if((fp=fopen("data","ab+"))==NULL){
        printf("cannot open\n");
        return;
    }
    while(!feof(fp))
        if(fread(&stu[m],LEN,1,fp))
            m++;
    if(m==0){
        printf("no record!\n");
        fclose(fp);
        return;
    }
    for(i=0;i<m-1;i++){
        for(j=i+1;j<m;j++){
            if(stu[i].num>stu[j].num){
                strcpy(stemp.name,stu[i].name);
                stemp.num=stu[i].num;
                stemp.elec=stu[i].elec;
                stemp.expe=stu[i].expe;
                stemp.requ=stu[i].requ;
                stemp.sum=stu[i].sum;
                stu[i]=stu[j];
                strcpy(stu[j].name,stemp.name);
                stu[j].num=stemp.num;
                stu[j].elec=stemp.elec;
                stu[j].expe=stemp.expe;
                stu[j].requ=stemp.requ;
                stu[j].sum=stemp.sum;
            }
        }
    }
    printf("Sort data.......");
    if((fp=fopen("data","wb"))==NULL){
        printf("cannot open\n");
        return;
    }
    for(i=0;i<m;i++)
        if(fwrite(&stu[i],LEN,1,fp)!=1){
            printf("cannot save!");
            getch();
        }
    fclose(fp);

}
void total(){
    FILE *fp;
    int m=0;
    if((fp=fopen("data","ab+"))==NULL){
        printf("cannot open\n");
        return;
    }
    while(!feof(fp))
        if(fread(&stu[m],LEN,1,fp))
            m++;
    if(m==0){
        printf("no record!\n");
        fclose(fp);
        return;
    }
    printf("the class are %d students!\n",m);
    fclose(fp);
}