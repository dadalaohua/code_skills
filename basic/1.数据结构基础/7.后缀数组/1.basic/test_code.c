#include <stdio.h>
#include <string.h>

#define N 1001

int SA[N];      //后缀数组
int heigt[N];   //前缀数组 
int c[N];       //辅助数组（计数排序）
int rank[N];    //名次数组
int X[N];       //关键1序
int Y[N];       //关键2序

int cmp(int *r, int a, int b, int l)
{
    return r[a]==r[b] && r[a+l]==r[b+l];
}

void gethzsz(int *r,int n)
{
    int i, j, p, m=127;
    int *tem, *x = X, *y = Y;//x y分别代表数组X Y的首地址
    
    for(i = 0; i < m; i++)
        c[i] = 0; //计数排序法
    
    for(i = 0; i < n; i++)
        c[r[i]]++, x[i]=r[i];
    
    for(i = 1; i < m;i++)
        c[i] += c[i-1];
    
    for(i = n-1; i >= 0; i--)
        SA[--c[x[i]]] = i;//得到初始SA 

    for(j = 1; j <= n; j <<= 1)// j代表当前所求长度 
    {
        for(p=0,i=n-j;i<n;i++)
            y[p++]=i;//将后缀长度小于等于当前长度的放在
        
        for(i=0;i<n;i++)
            if(SA[i]>=j)
                y[p++]=SA[i]-j;//后移操作 在第一关键序的基础上排第二关键序
        
        for(i=0;i<m;i++)
            c[i]=0;   //实质是 因为第一关键序字串后移当前长度直接作为第二关键序
        
        for(i=0;i<n;i++)
            c[x[i]]++;
        
        for(i=1;i<m;i++)
            c[i]+=c[i-1];
        
        for(i=n-1;i>=0;i--)
            SA[--c[x[y[i]]]]=y[i];//按第二关键字排序
        
        tem = x;
        x = y;
        y = tem;
        x[SA[0]] = 0;
        p = 1;
        
        for(i = 1; i < n; i++)
            x[SA[i]] = cmp(y,SA[i], SA[i-1], j) ? p - 1 : p++;
        
        if(p > n)
            break;
        
        m = p;
    }
}
void getheigt(int *r ,int n)
{
    int i, j, k = 0; heigt[0] = 0;
    for(i = 0; i < n; i++)
        rank[SA[i]] = i;
    
    for(i = 0; i < n; i++)
    {   
        if(!rank[i])
            continue;//排除 0首项
        
        if(k)
            --k;
        
        j = SA[rank[i]-1];  //j=当前一个名次字串前一个字串（ 看是否位该串前缀） 
        while(i + k < n && j + k < n && r[i+k] == r[j+k])
            k++;
        
        heigt[rank[i]] = k;//当前坐标 的前缀 
    }
}
int main(int argc, char* argv[])
{  
    char str[N];
    int len, i, j;
    int r[N];
    
    while(scanf("%s", str) != EOF)
    {
        len = strlen(str);
        for(i = 0; i < len; i++)
            r[i] = str[i];
        
        gethzsz(r, len);
        getheigt(r, len);
        
        puts("--------------All Suffix--------------");
        for(i = 0; i < len; ++i)
        {
            printf("%d:\t",i);
            for(j = i; j < len; ++j)
                printf("%c", str[j]);
            puts("");
        }
        puts("");
        
        puts("-------------After sort---------------");
        for(i = 0; i < len; ++i)
        {
            printf("SA[%2d ] = %2d\t", i, SA[i]+1);
            for(j = SA[i]; j < len; ++j)
                printf("%c", str[j]);
            puts("");
        }
        puts("");
        
        puts("---------------Height-----------------");
        for(i = 0; i < len; ++i)
            printf("height[%2d ]=%2d \n", i, heigt[i]);
        puts("");
        
        puts("----------------Rank------------------");
        for(i = 0; i < len; ++i)
            printf("Rank[%2d ] = %2d\n", i, rank[i]+1);
        puts("------------------END-----------------");
    }

    return 0;
}
