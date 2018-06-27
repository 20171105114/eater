//
//  main.c
//  评委评分
//
//  Created by lishuxin on 2018/6/27.
//  Copyright © 2018年 lishuxin. All rights reserved.
//

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
struct student
{char num[10];
    char name[10];
    char sex[5];
    char  age[2];
    int remark;
    struct student *prior;
    struct student *next;
}l;
struct student *start,*last;
void enter(),list(),save(),
load(),delete_();
void store(struct student *g);
meun(),score();
main()
{
    char s[6],a[6];
    start=last=NULL;
       load();
    for(;;){
             switch(meun()){
                     case 1:enter();
                 break;
                     case 2:list();
                 break;
                     case 3:save();
                 break;
                     case 4:delete_();
                 break;
                     case 5:score();
                 break;
                 case 6:exit(0);}
              }
}
meun()
{char s[10];
    int c;
    printf("\t选手信息管理系统\n");
    printf("\t------------------------------------------\n");
    printf("\t[1.选手基本信息录入]  [2.选手基本信息显示]\n");
    printf("\t------------------------------------------\n");
    printf("\t[3.选手基本信息保存]  [4.选手基本信息删除]\n");
    printf("\t------------------------------------------\n");
    printf("\t[5.评委为选手打分  ]  [6.退出管理系统    ]\n");
    printf("\t------------------------------------------\n");
    printf("\t请按数字选择");
    gets(s);
    c=atoi(s);
    if(c<=7&&c>=1)
        return(c);
}
void enter()
{
    struct student *info;
    info=(struct student *)malloc(sizeof(struct student));
    if(!info){
        printf("\tEMS run out of!\n");
        return;}
    for(;;){
        info=(struct student *)malloc(sizeof(struct student));
            if(!info){
                printf("\tEMS run out of!\n");
                return;}
        printf("\t输入姓名:");gets(info->name);
        printf("\n");
        if(!*info->name) break;
        printf("\t输入号码:");gets(info->num);
        printf("\n");
        printf("\t输入性别:");gets(info->sex);
        printf("\n");
        printf("\t输入年龄:");gets(info->age);
        printf("\n");
        info->remark=0;
        store(info);
    }
}
void store(struct student *g)
{
        if(last==NULL){
        g->next=NULL;
        g->prior=NULL;
        last=g;
        start=g;
        return;
    }
    g->next=NULL;
    g->prior=last;
    last->next=g;
    last=g;
}
void display(struct student *info)
{
    printf("\t姓名:%s\n",info->name);
    printf("\t号码:%s\n",info->num);
    printf("\t性别:%s\n",info->sex);
    printf("\t年龄:%s\n",info->age);
    printf("\t分数:%d\n",info->remark);
    return;
}
void list()
{
    struct student *info;
        info=start;
        while(info){
        display(info);
        info=info->next;
    }
}
struct student *find(struct student *p)
{int a,b;
    struct student *info;
    info=start;
    if(!info){
        printf("\tFile not load!\n");
        return(NULL);
    }
        while(info){
            if(!strcmp(p->name,info->name)){
            return(info);}
        info=info->next;
    }
    printf("\t无此记录\n");
    return(NULL);
}
void delete_()
{
    struct student *info;
        printf("\t输入需要删除记录的姓名:");
    info=(struct student *)malloc(sizeof(struct student));
    gets(info->name);
    info=find(info);
    if(!info) return;
    if(!(info==start)&&!(info==last)){
        info->next->prior=info->prior;
        info->prior->next=info->next;
    }
    else{if((info->prior==NULL)&&(info->next==NULL))
        last=start=NULL;
    else{
        if(info==last){
            info->prior->next=NULL;
            last=info->prior;
        }
        else{
            info->next->prior=NULL;
            start=info->next;
        }}
    }
    free(info);
    return;
}
void save()
{struct student *info;
    FILE *fp;
    if((fp=fopen("f:\\student.kbm","wb"))==NULL){
        printf("\terror\n");
        return;
    }
    info=start;
    printf("\tsaving!\n");
    while(info){
        fwrite(info,sizeof(struct student),1,fp);
        info=info->next;
    }
    fclose(fp);
}
void load()
{
    struct student *info;
    FILE *fp;
    if((fp=fopen("f:\\student.kbm","rb"))==NULL){
        printf("\terror\n");
        return;
    }
    info=(struct student *)malloc(sizeof(struct student));
    if(!info){
        printf("\tEMS run out of!\n");
        return;
    }
    printf("\tloading!\n");
    info->prior=NULL;
    info->next=NULL;
    start=last=info;
    while(!feof(fp)){
        if(1!=fread(info,sizeof(struct student),1,fp)) break;
        info->next=(struct student *)malloc(sizeof(struct student));
        if(!info->next){
            printf("\tEMS run out of!\n");
            return;
        }
        last=info;
        info=info->next;
    }
    free(info);
    last->next=NULL;
    fclose(fp);
}
int sum()
{
    int a[5],sum=0,i,max,min;
    for(i=0;i<=4;i++){
        printf("\t输入第%d个评委的打分",i+1);
        scanf("%d",&a[i]);
        getchar();
        sum=a[i]+sum;
    }
    max=min=a[0];
    for(i=1;i<=4;i++)
    {
        if(max<a[i])
            max=a[i];
        if(min>a[i])
            min=a[i];
    }
    sum=(sum-max-min)/3;
    return(sum);
}
score()
{   struct student *info;
        printf("\t输入需要打分选手的姓名:");
    info=(struct student *)malloc(sizeof(struct student));
    gets(info->name);
    info=find(info);
    info->remark=sum();
    return;
}
