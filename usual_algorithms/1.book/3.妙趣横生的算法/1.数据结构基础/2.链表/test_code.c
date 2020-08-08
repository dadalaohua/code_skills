#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct node{
    ElemType data;   /*数据域*/
    struct node *next;  /*指针域*/
}LNode,*LinkList;

LinkList GreatLinkList(int n)
{
    LinkList p,r,list=NULL;
    ElemType e;
    int i;
    
    for(i = 1; i <= n; i++)
    {
        scanf("%d",&e);
        p = (LinkList)malloc(sizeof(LNode));
        p->data = e;
        p->next = NULL;
        if(!list)
            list = p;
        else
            r->next = p;
        r = p;
    }
    
    return list;
}

void insertList(LinkList *list,LinkList q,ElemType e)
{
    LinkList p;
    
    p = (LinkList)malloc(sizeof(LNode));
    p->data = e;
    
    if(!*list)
    {
        *list=p;
        p->next=NULL;
    }
    else
    {
        p->next=q->next;
        q->next=p;
    }    
}

void delLink(LinkList *list ,LinkList q)
{
    LinkList r;
    
    if(q == *list)
    {
        *list=q->next;
        free(q);
    }
    else
    {
        for(r=*list;r->next!=q;r=r->next);
        
        if(r->next!=NULL)
        {
            r->next=q->next;
            free(q);
        }
    }
}

void  destroyLinkList(LinkList *list)
{
    LinkList p,q;
    
    p=*list;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    *list=NULL;
} 

/****************************/

int main(int argc, char* argv[])
{
    int e,i;
    LinkList l,q;
    
    q=l=GreatLinkList(1);   /*创建一个链表结点，q和l指向该结点*/
    scanf("%d",&e);
    while(e)             /*循环地输入数据，同时插入新生成的结点*/
    {
        insertList(&l,q,e) ;
        q=q->next;
        scanf("%d",&e);
    }
    q = l;
    printf("The content of the linklist\n");
    while(q)          /*输出链表中的内容*/
    {
      printf("%d ",q->data);
      q=q->next;
    }
    q=l;
    printf("\nDelete the fifth element\n");
    for(i = 0; i < 4; i++)    /*将指针q指向链表第5个元素*/
    {
        if (q == NULL) {
            printf("The length of the linklist is smaller than 5 !");
            return;
        }
        q=q->next;
    }
    delLink(&l,q);     /*删除q所指的结点*/
    q = l;
    while(q)            /*打印出删除后的结果*/
    {
        printf("%d ",q->data);
        q=q->next;
    }
    destroyLinkList(&l);  /*释放掉该链表*/
    
    printf("\n");
    
    return 0;
}