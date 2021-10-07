#include <stdio.h>
#include "App.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    stObj *Obj;

    Obj = sCreate(3,5); //内部构造结构体 
    Obj->public.member1 = 10;

    Obj->public.member1 = 6;
    Obj->public.member2 = 10;

    printf("member1 = %d\n",Obj->public.member1);  //调用OK，member1被公开
    printf("member2 = %d\n",Obj->public.member2);  //调用OK，member1被公开

    // printf("member1 = %d\n",Obj->private.member1); //调用失败,因为member1被隐藏
    // printf("member2 = %d\n",Obj->private.member2);  //调用失败,因为member2被隐藏

    printf("private result = %d\n",sAddprivate(Obj));  //调用相应的接口 
    printf("public result = %d\n",sAddpublic(Obj));  //调用相应的接口 
    
    return 0;
}