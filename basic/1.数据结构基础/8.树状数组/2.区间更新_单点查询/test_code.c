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
    int k, x, y;
    
    //设置数据长度为10
    n = 10;
    
    for(int i = 1; i <= n; i++){
        a[i] = i;
        updata(i, a[i] - a[i - 1]);   //输入初值的时候，也相当于更新了值
    }
    
    //[x,y]区间内的数都加上k
    k = 10;
    x = 5;
    y = 9;
    updata(x, k);       //A[x] - A[x-1]增加k
    updata(y + 1, -k);  //A[y+1] - A[y]减少k
    
    //查询i位置的值
    sum = getsum(8);
    printf("%d val %d\n", 8, sum);
    
    return 0;
}