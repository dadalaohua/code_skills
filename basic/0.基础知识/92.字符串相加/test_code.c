#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//不需要动态申请
int stringadd(char * num1, char *num2, char *result) {
    int i = strlen(num1) - 1, j = strlen(num2) - 1, add = 0;
    int len = 0;
    while (i >= 0 || j >= 0 || add != 0) {
        int x = i >= 0 ? num1[i] - '0' : 0;
        int y = j >= 0 ? num2[j] - '0' : 0;
        int sum = x + y + add;
        result[len++] = '0' + sum % 10;
        add = sum / 10;
        i--, j--;
    }
    
    int reversal_len = len / 2;
    int t;
    for (int i = 0; i < reversal_len; i++) {
        t = result[i];
        result[i] = result[len - i - 1];
        result[len - i - 1] = t;
    }
    result[len] = 0;
    return len;
}

//需要动态申请，返回值需要自行释放
char* addStrings(char* num1, char* num2) {
    int i = strlen(num1) - 1, j = strlen(num2) - 1, add = 0;
    char* ans = (char*)malloc(sizeof(char) * ((i > j ? i : j) + 3));
    int len = 0;
    while (i >= 0 || j >= 0 || add != 0) {
        int x = i >= 0 ? num1[i] - '0' : 0;
        int y = j >= 0 ? num2[j] - '0' : 0;
        int result = x + y + add;
        ans[len++] = '0' + result % 10;
        add = result / 10;
        i--, j--;
    }
    // 计算完以后的答案需要翻转过来
    for (int i = 0; 2 * i < len; i++) {
        int t = ans[i];
        ans[i] = ans[len - i - 1], ans[len - i - 1] = t;
    }
    ans[len++] = 0;
    return ans;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char num1[] = "123456789";
    char num2[] = "33366699";
    char result[20] = {0};
    stringadd(num1, num2, result);
    printf("%s + %s = %s\n", num1, num2, result);
    
    char *ans = addStrings(num1, num2);
    printf("%s + %s = %s\n", num1, num2, ans);
    free(ans);
    
    return 0;
}