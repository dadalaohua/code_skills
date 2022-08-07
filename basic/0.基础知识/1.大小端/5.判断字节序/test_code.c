#include <stdio.h>
//#include <stdlib.h>
#include <endian.h>
#include <stdint.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

void check(void)  
{
    if(BYTE_ORDER == LITTLE_ENDIAN)
        printf("Little-Endian\n"); 
    else if(BYTE_ORDER == BIG_ENDIAN)
        printf("Big-Endian\n");
    else
        printf("PDP-Endian\n");

#if BYTE_ORDER == LITTLE_ENDIAN
    printf("Little-Endian\n"); 
#elif BYTE_ORDER == BIG_ENDIAN
    printf("Big-Endian\n");
#else
    printf("PDP-Endian\n");
#endif
    
    if(__BYTE_ORDER == __LITTLE_ENDIAN)
        printf("Little-Endian\n"); 
    else if(__BYTE_ORDER == __BIG_ENDIAN)
        printf("Big-Endian\n");
    else
        printf("PDP-Endian\n");
    
#if __BYTE_ORDER == __LITTLE_ENDIAN
    printf("Little-Endian\n"); 
#elif __BYTE_ORDER == __BIG_ENDIAN
    printf("Big-Endian\n");
#else
    printf("PDP-Endian\n");
#endif

//https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html

    if(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
        printf("Little-Endian\n"); 
    else if(__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
        printf("Big-Endian\n");
    else
        printf("PDP-Endian\n");
    
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    printf("Little-Endian\n"); 
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    printf("Big-Endian\n");
#else
    printf("PDP-Endian\n");
#endif
}

void check2(void)  
{
    int32_t val = 0x44332211;
    int8_t *ptr = (int8_t *)&val;

    printf("\n0x%x 0x%x 0x%x 0x%x\n", ptr[0], ptr[1], ptr[2], ptr[3]);
    
    if(ptr[0] == 0x11)
        printf("Little-Endian\n"); 
    else if(ptr[0] == 0x44)
        printf("Big-Endian\n");
    else
        printf("PDP-Endian\n");
    
    if(ptr[3] == 0x44)
        printf("Little-Endian\n"); 
    else if(ptr[3] == 0x11)
        printf("Big-Endian\n");
    else
        printf("PDP-Endian\n");
}

void check3(void)  
{
    union
    {  
        int32_t num;
        int8_t buf[4];
    } val;
    
    val.num = 0x44332211;
    printf("\n0x%x 0x%x 0x%x 0x%x\n", val.buf[0], val.buf[1], val.buf[2], val.buf[3]);
    
    if(val.buf[0] == 0x11)
        printf("Little-Endian\n"); 
    else if(val.buf[0] == 0x44)
        printf("Big-Endian\n");
    else
        printf("PDP-Endian\n");
    
    if(val.buf[3] == 0x44)
        printf("Little-Endian\n"); 
    else if(val.buf[3] == 0x11)
        printf("Big-Endian\n");
    else
        printf("PDP-Endian\n");
}

void check4(void)  
{
    union
    {  
        int32_t num;
        int8_t x;
    } val;
    
    val.num = 0x44332211;
    printf("\n0x%x\n", val.x);
    
    if(val.x == 0x11)
        printf("Little-Endian\n"); 
    else if(val.x == 0x44)
        printf("Big-Endian\n");
    else
        printf("PDP-Endian\n");
}

int main(int argc, char* argv[])
{
    printf("%d\n", __FLOAT_WORD_ORDER__);
    printf("%d\n", __FLOAT_WORD_ORDER);
    printf("\n");
    
    printf("%d\n", __BYTE_ORDER__);
    printf("%d\n", __BYTE_ORDER);
    printf("%d\n", BYTE_ORDER);
    printf("\n");
    
    printf("%d\n", __ORDER_LITTLE_ENDIAN__);
    printf("%d\n", __ORDER_BIG_ENDIAN__);
    printf("%d\n", __ORDER_PDP_ENDIAN__);
    printf("\n");
    
    printf("%d\n", __LITTLE_ENDIAN);
    printf("%d\n", __BIG_ENDIAN);
    printf("%d\n", __PDP_ENDIAN);
    printf("\n");
    
    printf("%d\n", LITTLE_ENDIAN);
    printf("%d\n", BIG_ENDIAN);
    printf("%d\n", PDP_ENDIAN);
    printf("\n");
    
    check();
    check2();
    check3();
    check4();
    
    return 0;
}