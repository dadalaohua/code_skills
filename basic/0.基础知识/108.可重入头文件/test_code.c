// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef unsigned char uint8_t;

// 2位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA2Table[4] = {

#undef MFUNC_IN_START
#undef MFUNC_IN_DELTA

#define MFUNC_IN_START    0
#define MFUNC_IN_COUNT    4
#define MFUNC_IN_DELTA    85
#include "mf_u8_fill_dec.h"

};

// 4位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA4Table[16] = {

#undef MFUNC_IN_START
#undef MFUNC_IN_DELTA

#define MFUNC_IN_START    0
#define MFUNC_IN_COUNT    16
#define MFUNC_IN_DELTA    17
#include "mf_u8_fill_dec.h"

};


// 8位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA8Table[256] = {

#undef MFUNC_IN_START
#undef MFUNC_IN_DELTA

#define MFUNC_IN_START    0
#define MFUNC_IN_COUNT    128
#include "mf_u8_fill_dec.h"

#undef MFUNC_IN_START
#undef MFUNC_IN_DELTA

#define MFUNC_IN_START    128
#define MFUNC_IN_COUNT    128
#include "mf_u8_fill_dec.h"

};

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i;
    
    printf("c_chAlphaA2Table : \n");
    for(i = 0; i < 4; i++) {
        printf("%d ", c_chAlphaA2Table[i]);
    }
    printf("\n");
    
    printf("c_chAlphaA4Table : \n");
    for(i = 0; i < 16; i++) {
        printf("%d ", c_chAlphaA4Table[i]);
    }
    printf("\n");
    
    printf("c_chAlphaA8Table : \n");
    for(i = 0; i < 256; i++) {
        printf("%d ", c_chAlphaA8Table[i]);
    }
    printf("\n");
    
    return 0;
}