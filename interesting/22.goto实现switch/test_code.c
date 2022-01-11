#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void gotoswitch(int val) {
    static void* array[] = { &&lable0, &&lable1, &&lable2, &&lable3, &&lable4, &&lable5};
    
    if(val >= (sizeof(array)/sizeof(void*)))
        goto other;
    
    goto *array[val];
lable0:
    printf("lable0\n");
    goto end;
lable1:
    printf("lable1\n");
    goto end;
lable2:
    printf("lable2\n");
    goto end;
lable3:
    printf("lable3\n");
    goto end;
lable4:
    printf("lable4\n");
    goto end;
lable5:
    printf("lable5\n");
    goto end;
other:
    printf("other %d\n", val);
    goto end;
end:
    return;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    for(int i = 0; i < 10; i++)
        gotoswitch(i);
    return 0;
}