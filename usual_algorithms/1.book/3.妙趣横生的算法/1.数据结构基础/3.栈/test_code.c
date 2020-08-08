#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT 10

typedef  char ElemType;

typedef struct{
    ElemType *base;
    ElemType *top;
    int stacksize;
}sqStack;

void initStack(sqStack *s)
{
    /*内存中开辟一段连续空间作为栈空间，首地址赋值给s->base*/
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if(!s->base) exit(0);     /*分配空间失败*/
    s->top = s->base;       /*最开始，栈顶就是栈底*/
    s->stacksize = STACK_INIT_SIZE;   /*最大容量为STACK_INIT_SIZE */
}

void Push(sqStack *s, ElemType e)
{
    if(s->top - s->base >= s->stacksize)
    {
        /*栈满，追加空间*/
        s->base = (ElemType *)realloc(s->base, (s->stacksize + STACKINCREMENT)*sizeof(ElemType));
        
        if(!s->base)
            exit(0);   /*存储分配失败*/
        
        s->top = s->base + s->stacksize;
        s->stacksize = s->stacksize + STACKINCREMENT; /*设置栈的最大容量*/
    }
    
    *(s->top) = e;  /*放入数据*/
    s->top++;
}

void Pop(sqStack *s , ElemType *e)
{
    if(s->top == s->base)
        return;
    
    *e = *--(s->top); 
}

int StackLen(sqStack s)
{
    return (s.top - s.base); 
}

void DestroyStack(sqStack *s)
{
    free(s->base);
    s->base = s->top = NULL;    /*栈底栈顶指针置NULL*/
    s->stacksize = 0;           /*设置栈的最大容量为0*/
}

/****************************/

int main(int argc, char* argv[])
{
    ElemType c;
    sqStack s;
    int len, i;
    unsigned int sum = 0;

    printf("Please input a Binary digit\n");

    initStack(&s);  /*创建一个栈，用来存放二进制字符串*/
    /*输入0/1字符表示的二进制数，以#结束*/
    scanf("%c",&c);
    while(c != '#')
    {
        Push(&s, c);
        scanf("%c",&c);
    }
    getchar();
    len = StackLen(s);                  /*得到栈中的元素个数，即二进制数的长度*/

    for(i = 0; i < len; i++)
    {
        Pop(&s, &c);
        sum = sum + (c-48) * pow(2, i);  /*转换为十进制*/
    }
    printf("Decimal is 0x%x\n", sum);
    DestroyStack(&s);                   /*销毁栈空间*/
    
    return 0;
}