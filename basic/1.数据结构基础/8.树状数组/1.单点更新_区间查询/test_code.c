#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int n;
int a[50005] = {0}, c[50005] = {0}; //对应原数组和树状数组

int lowbit(int x){
    return x&(-x);
}

void updata(int i, int k) {    //在i位置加上k
    while(i <= n){
        c[i] += k;
        i += lowbit(i);
    }
}

int getsum(int i) {        //求A[1 ~ i]的和
    int res = 0;
    while(i > 0) {
        res += c[i];
        i -= lowbit(i);
    }
    return res;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int sum;
    
    //设置数据长度为10
    n = 10;
    
    for(int i = 1; i <= n; i++){
        a[i] = i;
        updata(i, a[i]);   //输入初值的时候，也相当于更新了值
    }
    
    sum = getsum(5); //获取数组a[1] ~ a[5]的和
    printf("1 + ... + 5 = %d\n", sum);
    
    sum = getsum(10); //获取数组a[1] ~ a[10]的和
    printf("1 + ... + 10 = %d\n", sum);
    
    sum = getsum(10) - getsum(5 - 1); //获取数组a[5] ~ a[10]的和
    printf("5 + ... + 10 = %d\n", sum);
    
    //单点更新
    a[8] += 5;
    updata(8, 5);
    
    //区间查询
    sum = getsum(10); //获取数组a[1] ~ a[10]的和
    printf("1 + ... + 10 = %d\n", sum);
    
    sum = getsum(10) - getsum(5 - 1); //获取数组a[5] ~ a[10]的和
    printf("5 + ... + 10 = %d\n", sum);
    
    //单点更新
    a[9] -= 10;
    updata(9, -10);
    
    //区间查询
    sum = getsum(10); //获取数组a[1] ~ a[10]的和
    printf("1 + ... + 10 = %d\n", sum);
    
    sum = getsum(10) - getsum(5 - 1); //获取数组a[5] ~ a[10]的和
    printf("5 + ... + 10 = %d\n", sum);
    
    return 0;
}