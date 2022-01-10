#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "char_conversion.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
char txt_src[] = "123你好abc";
char txt_dir[32];
char txt_rec[32];

int main(int argc, char* argv[])
{
    utf8ToGb2312(txt_dir, sizeof(txt_dir), txt_src, strlen(txt_src));
    
    printf("%s\n", txt_src);
    
    for(int i = 0; i < strlen(txt_dir); i++)
        printf("0x%x ", (unsigned char)txt_dir[i]);
    printf("\n");
    
    printf("%s\n", txt_dir);
    
    gb2312ToUtf8(txt_rec, sizeof(txt_rec), txt_dir, strlen(txt_dir));
    
    for(int i = 0; i < strlen(txt_rec); i++)
        printf("0x%x ", (unsigned char)txt_rec[i]);
    printf("\n");
    
    printf("%s\n", txt_rec);
    
    return 0;
}