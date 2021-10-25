#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kstring.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int *fields, n, i;
    ks_tokaux_t aux;
    char *p;
    kstring_t *s;
    
    s = (kstring_t*)calloc(1, sizeof(kstring_t));
    
    // test ksprintf() 对应sprintf
    ksprintf(s, " abcdefg:  %d ", 100);
    printf("'%s'\n", s->s);
    
    // test ksplit()
    // 返回按分隔符拆分的"s"，其中*n是组件数
    fields = ksplit(s, 0, &n);
    for (i = 0; i < n; ++i)
        printf("field[%d] = '%s'\n", i, s->s + fields[i]);
    
    // test kstrtok() 对应strtok 分解字符串
    //kstrtok()与strtok_r()类似，只是str没有被修改，str和sep都可以为NULL。
    //为了提高效率，如果sep没有更改，实际上建议在后续调用中将两者都设置为NULL。
    s->l = 0; //字符串长度置0
    //p = kstrtok("ab:cde:fg/hij::k", ":/", &aux) 以":/"为分隔符，获取字符串"ab:cde:fg/hij::k"中的子串，第一次获取结果为"ab"
    //p = kstrtok(0, 0, &aux) 后续的获取sep没有更改，可以将str和sep设置为NULL
    for (p = kstrtok("ab:cde:fg/hij::k", ":/", &aux); p; p = kstrtok(0, 0, &aux)) {
        kputsn(p, aux.p - p, s);    //将长度为aux.p - p的字符串p，写入s
        kputc('\n', s); //将'\n'写入s
    }
    printf("%s", s->s); //打印出分解子串的结果
    printf("%s", ks_str(s));//或者使用接口ks_str
    printf("%d\n", s->l); //打印出分解子串的长度
    printf("%d\n", ks_len(s)); //或者使用接口ks_len
    
    s->l = 0; //字符串长度置0
    //将字符串放入
    kputs("hello world", s);
    printf("%s\n", ks_str(s));
    
    // free
    free(s->s);
    free(s);
    free(fields);
    
/************************************************************************/
{
    static char *str = "abcdefgcdgcagtcakcdcd";
    static char *pat = "cd";
    char *ret, *s = str;
    int *prep = 0;
    
    //test kstrstr() 对应strstr 查找字符串
    while ((ret = kstrstr(s, pat, &prep)) != 0) {
        printf("match: %s\n", ret);
        s = ret + prep[0];
    }
    free(prep);
}

    return 0;
}