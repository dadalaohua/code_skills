#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include <locale.h>
#include <wchar.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    https://bbs.csdn.net/topics/390538331?page=1
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{

    int i;
    int ret;
    size_t size;
    size_t ret_size;
    wchar_t *wstr = NULL;
    void *tmp;
 
    setlocale(LC_CTYPE, "en_US.UTF-8");
    for (i = 1; i < argc; i++) {
        size = strlen(argv[i]) + 1;
        tmp = realloc(wstr, sizeof(wchar_t) *  size);
        if (NULL == tmp) {
            if (NULL != wstr) {
                free(wstr);
            }
            perror("alloc error");
            return 1;
        }
        wstr = tmp;
 
        ret_size = mbstowcs(wstr, argv[i], size);
        if (ret_size == (size_t)(-1)) {
            fprintf(stderr, "Invalid mbs\n");
            continue;
        }
        printf("[%s] %d\n", argv[i], (ret = wcswidth(wstr, ret_size)));
        if (ret == -1) {
            fprintf(stderr, "Invalid wcs\n");
        }
    }
 
    if (wstr) {
        free(wstr);
    }

    return 0;
}