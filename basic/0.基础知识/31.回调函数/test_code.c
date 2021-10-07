#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct gfun{
    int (*pfun)(int);
}gfun;

int myfun(int data)
{
    printf("get data:%d\n",data);
    
    return (data*2);
}

int double_data(int data,int (*fun)(int))
{
    return ((*fun)(data));
}  

/****************************/

int main(int argc, char* argv[])
{
    int ret;
    gfun gcode;
    
    gcode.pfun = myfun;
    ret = double_data(100, gcode.pfun);
    
    printf("return data:%d\n",ret);
    
    ret = double_data(50, myfun);
    
    printf("return data:%d\n",ret);
    
    return 0;
}