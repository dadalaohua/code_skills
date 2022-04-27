#include <stdio.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//lawful good
void test_lawful_good(int *buf, int len) {
    
    for(int i = 0; i < len; i++) {
        buf[0] = i;
        buf += 1;
    }
}

//neutral good
void test_neutral_good(int *buf, int len) {
    
    for(int i = 0; i < len; i++) {
        *buf = i;
        buf++;
    }
}

//chaotic good
void test_chaotic_good(int *buf, int len) {
    
    for(int i = 0; i < len; i++) {
        buf++;
        buf[-1] = i;
    }
}

//lawful neutral
void test_lawful_neutral(int *buf, int len) {
    
    for(int i = 0; i < len; i++) {
        (buf++)[0] = i;
    }
}

//true neutral
void test_true_neutral(int *buf, int len) {
    
    for(int i = 0; i < len; i++) {
        *buf++ = i;
    }
}

//chaotic neutral
void test_chaotic_neutral(int *buf, int len) {
    
    for(int i = 0; i < len; i++) {
        buf++[0] = i;
    }
}

//lawful evil
void test_lawful_evil(int *buf, int len) {
    
    for(int i = 0; i < len; i++) {
        0[buf++] = i;
    }
}

//neutral evil
void test_neutral_evil(int *buf, int len) {
    
    for(int i = 0; i < len; i++) {
        *((buf += 1) - 1) = i;
    }
}

//chaotic evil
void test_chaotic_evil(int *buf, int len) {
    char tmpbuf[len];
    char *p = tmpbuf;
    for(int i = 0; i < len; i++) {
        (~0)[p = (char *)(-~(size_t)p)] = i;
        //负数用补码表示，补码 = 反码 + 1
        //所以 -x = ~x + 1
        //因此
        //~0 => -1
        //-~(size_t)p => p + 1;
        //-1[p = p + 1] = i
        //
        //注意这里地址值是固定 + 1，而不是根据指针类型不同而不同
        //所以该函数传入int *类型是不能用该方法的
        //只能用单字节类型，如char *类型
    }
    
    for(int i = 0; i < len; i++) {
        //printf("%d, ", tmpbuf[i]);
        buf[i] = tmpbuf[i];
    }
    //printf("\n");
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int buf[10] = {0};
    
    memset(buf, 0, sizeof(buf));
    test_lawful_good(buf, sizeof(buf)/sizeof(int));
    printf("lawful good : ");
    for(int i = 0; i < sizeof(buf)/sizeof(int); i++) {
        printf("%d, ", buf[i]);
    }
    printf("\n");
    
    memset(buf, 0, sizeof(buf));
    test_neutral_good(buf, sizeof(buf)/sizeof(int));
    printf("neutral good : ");
    for(int i = 0; i < sizeof(buf)/sizeof(int); i++) {
        printf("%d, ", buf[i]);
    }
    printf("\n");
    
    memset(buf, 0, sizeof(buf));
    test_chaotic_good(buf, sizeof(buf)/sizeof(int));
    printf("chaotic good : ");
    for(int i = 0; i < sizeof(buf)/sizeof(int); i++) {
        printf("%d, ", buf[i]);
    }
    printf("\n");
    
    memset(buf, 0, sizeof(buf));
    test_lawful_neutral(buf, sizeof(buf)/sizeof(int));
    printf("lawful neutral : ");
    for(int i = 0; i < sizeof(buf)/sizeof(int); i++) {
        printf("%d, ", buf[i]);
    }
    printf("\n");
    
    memset(buf, 0, sizeof(buf));
    test_true_neutral(buf, sizeof(buf)/sizeof(int));
    printf("true neutral : ");
    for(int i = 0; i < sizeof(buf)/sizeof(int); i++) {
        printf("%d, ", buf[i]);
    }
    printf("\n");
    
    memset(buf, 0, sizeof(buf));
    test_chaotic_neutral(buf, sizeof(buf)/sizeof(int));
    printf("chaotic neutral : ");
    for(int i = 0; i < sizeof(buf)/sizeof(int); i++) {
        printf("%d, ", buf[i]);
    }
    printf("\n");
    
    memset(buf, 0, sizeof(buf));
    test_lawful_evil(buf, sizeof(buf)/sizeof(int));
    printf("lawful evil : ");
    for(int i = 0; i < sizeof(buf)/sizeof(int); i++) {
        printf("%d, ", buf[i]);
    }
    printf("\n");
    
    memset(buf, 0, sizeof(buf));
    test_neutral_evil(buf, sizeof(buf)/sizeof(int));
    printf("neutral evil : ");
    for(int i = 0; i < sizeof(buf)/sizeof(int); i++) {
        printf("%d, ", buf[i]);
    }
    printf("\n");
    
    memset(buf, 0, sizeof(buf));
    test_chaotic_evil(buf, sizeof(buf)/sizeof(int));
    printf("chaotic evil : ");
    for(int i = 0; i < sizeof(buf)/sizeof(int); i++) {
        printf("%d, ", buf[i]);
    }
    printf("\n");
    
    return 0;
}