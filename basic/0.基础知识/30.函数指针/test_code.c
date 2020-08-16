#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//方法一
void (*pfun_1)(int data);

//方法二
typedef void (*pfun_2)(int data);

//方法三
typedef struct gfun{
    void (*pfun)(int);
}gfun;

void myfun(int data)
{
    printf("get data:%d\n",data);
}

/****************************/

int main(int argc, char* argv[])
{
    //方法一
    pfun_1 = myfun;
    
    (*pfun_1)(50);
    
    //方法二
    pfun_2 p  = myfun;
    
    p(100);
    
    //方法三
    gfun gcode={
        .pfun = myfun,
    };
    gcode.pfun(150);
    
    return 0;
}