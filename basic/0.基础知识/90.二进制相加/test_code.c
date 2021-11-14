#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void reserve(char* s) {
    int len = strlen(s);
    for (int i = 0; i < (len / 2); i++) {
        char t = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = t;
    }
}


//方式一:需要外部释放申请的内存
char * addBinary(char * a, char * b) {
    int len_a = strlen(a), len_b = strlen(b);
    int n = len_a > len_b ? len_a : len_b;
    int carry = 0, len = 0;
    char* ans = (char*)malloc(sizeof(char) * (n + 2));
    char* a_tmp;
    char* b_tmp;

    a_tmp = strdup(a);
    b_tmp = strdup(b);
    reserve(a_tmp);
    reserve(b_tmp);
    
    for (int i = 0; i < n; ++i) {
        carry += i < len_a ? (a_tmp[i] == '1') : 0;
        carry += i < len_b ? (b_tmp[i] == '1') : 0;
        ans[len++] = carry % 2 + '0';
        carry /= 2;
    }

    if (carry) {
        ans[len++] = '1';
    }
    ans[len] = '\0';
    reserve(ans);
    
    free(a_tmp);
    free(b_tmp);

    return ans;
}

//方式二:不需要外部释放申请的内存，但内部需要申请释放内存
int addBinaryString(char * a, char * b, char *buf, unsigned int buflen) {
    int len_a = strlen(a), len_b = strlen(b);
    int n = len_a > len_b ? len_a : len_b;
    int carry = 0, len = 0;
    char* a_tmp;
    char* b_tmp;
    
    if(buflen < (n + 2))
        return -1;
    
    a_tmp = strdup(a);
    b_tmp = strdup(b);
    reserve(a_tmp);
    reserve(b_tmp);
    
    for (int i = 0; i < n; ++i) {
        carry += i < len_a ? (a_tmp[i] == '1') : 0;
        carry += i < len_b ? (b_tmp[i] == '1') : 0;
        buf[len++] = carry % 2 + '0';
        carry /= 2;
    }

    if (carry)
        buf[len++] = '1';
    
    buf[len] = '\0';
    
    reserve(buf);
    
    free(a_tmp);
    free(b_tmp);

    return 0;
}

//方式三:不需要外部释放申请的内存，但不需要内部申请释放内存，但是参数a和b不能是静态字符串
int addBinaryString2(char * a, char * b, char *buf, unsigned int buflen) {
    int len_a = strlen(a), len_b = strlen(b);
    int n = len_a > len_b ? len_a : len_b;
    int carry = 0, len = 0;
    
    if(buflen < (n + 2))
        return -1;
    
    reserve(a);
    reserve(b);
    
    for (int i = 0; i < n; ++i) {
        carry += i < len_a ? (a[i] == '1') : 0;
        carry += i < len_b ? (b[i] == '1') : 0;
        buf[len++] = carry % 2 + '0';
        carry /= 2;
    }

    if (carry)
        buf[len++] = '1';
    
    buf[len] = '\0';
    
    reserve(buf);

    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char buf[100];
    char *ptr;
    char a[] = "1010";
    char b[] = "10";
    
    ptr = addBinary("1010", "10");
    printf("%s\n", ptr);
    free(ptr);
    
    addBinaryString("1010", "10", buf, sizeof(buf));
    printf("%s\n", buf);
    
    addBinaryString2(a, b, buf, sizeof(buf));
    printf("%s\n", buf);
    
    return 0;
}