#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int n, m;
int a[50005] = {0};
int sum1[50005];    //(D[1] + D[2] + ... + D[n])
int sum2[50005];    //(1*D[1] + 2*D[2] + ... + n*D[n])

int lowbit(int x){
    return x&(-x);
}

void updata(int i,int k){
    int x = i;    //因为x不变，所以得先保存i值
    while(i <= n){
        sum1[i] += k;
        sum2[i] += k * (x-1);
        i += lowbit(i);
    }
}

int getsum(int i){        //求前缀和
    int res = 0, x = i;
    while(i > 0){
        res += x * sum1[i] - sum2[i];
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
    
    x = 5;
    y = 9;
    
    //求[x,y]区间和
    sum = getsum(y) - getsum(x - 1);
    printf("%d ~ %d sum %d\n", x, y, sum);
    
    //[x,y]区间内的数都加上k
    k = 10;

    updata(x, k);       //A[x] - A[x-1]增加k
    updata(y + 1, -k);  //A[y+1] - A[y]减少k
    
    //求[x,y]区间和
    sum = getsum(y) - getsum(x - 1);
    printf("%d ~ %d sum %d\n", x, y, sum);
    
    return 0;
}