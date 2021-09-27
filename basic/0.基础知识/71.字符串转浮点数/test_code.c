#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//m^n函数
//返回值:m^n次方.
unsigned int Pow(unsigned char m, unsigned char n)
{
    unsigned int result = 1;
    
    while(n--)
        result*=m;
    
    return result;
}

//str转换为数字,以','或者'*'结束
//buf:数字存储区
//dx:小数点位数,返回给调用函数
//返回值:转换后的数值
int Str2num(unsigned char *buf, unsigned char *dx)
{
    unsigned char *p = buf;
    unsigned int ires = 0, fres = 0;
    unsigned char ilen = 0, flen = 0, i;
    unsigned char mask = 0;
    int res;
    
    while(1) //得到整数和小数的长度
    {
        if(*p == '-')
        {
            mask |= 0x02;         //是负数
            p++;
        }
        
        if((*p == ',')||(*p == '*')||(*p == '\0'))
            break;              //遇到结束了
        
        if(*p=='.')
        {
            mask |= 0x01;
            p++;                    //遇到小数点了
        }
        else if((*p > '9')||(*p < '0'))   //有非法字符
        {   
            ilen = 0;
            flen = 0;
            
            break;
        }
        
        if(mask & 0x01)
            flen++;
        else
            ilen++;
        
        p++;
    }
    
    if(mask & 0x02)
        buf++; //去掉负号
    
    for(i=0;i<ilen;i++) //得到整数部分数据
    {  
        ires+=Pow(10,ilen-1-i)*(buf[i]-'0');
    }
    
    if(flen > 5)
        flen = 5;   //最多取5位小数
    
    *dx=flen;       //小数点位数
    
    for(i = 0; i < flen; i++) //得到小数部分数据
    {  
        fres += Pow(10, flen-1-i) * (buf[ilen+1+i]-'0');
    }
    
    res = ires * Pow(10, flen) + fres;
    
    if(mask & 0x02)
        res = -res;
    
    return res;
} 

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char buf1[128] = "123.45678";
    unsigned char buf2[128] = "-9876.54321";
    unsigned char buf3[128] = "-6543";
    unsigned char dx;
    int val;
    
    val = Str2num(buf1, &dx);
    printf("buf1 %s, val %d %d %f\n", buf1, val, dx, (float)val/Pow(10, dx));
    
    val = Str2num(buf2, &dx);
    printf("buf2 %s, val %d %d %f\n", buf2, val, dx, (float)val/Pow(10, dx));
    
    val = Str2num(buf3, &dx);
    printf("buf3 %s, val %d %d %f\n", buf3, val, dx, (float)val/Pow(10, dx));

    return 0;
}