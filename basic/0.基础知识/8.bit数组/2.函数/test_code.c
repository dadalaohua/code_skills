#include <stdio.h>
#include <stdlib.h>
#include "bitarray.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/************************************************************************/
//按指定的位数打印一个变量的位模式
void print_in_bitmode(unsigned int  to_print, unsigned bit){

    unsigned char *p_chs;
    p_chs =  malloc(bit+1);
    unsigned char *reset= p_chs;
    int  result,reminder;
    int i;
    
    result = to_print;
    reminder = 0;


    if(p_chs == NULL)
    {
        printf("NULL Pointer!\n");
        return;
    }
    //清零
    for(i=0;i<bit;i++)
    {
        *p_chs++ ='0';
    }
    *p_chs++ = (char)0x00;//空字符
    //把指针重新指向数组的开头
       p_chs=reset; 
       //p_chs -=(bit+1);//这种方式也可以把指针重新移到开头但是不好理解，而且存在隐患容易出错
    //把to_print转换成bit位的二进制
    while(result != 0)
    {

        reminder = result % 2;
        result /= 2;
        if(*p_chs != (char)0x00 )
        {
        *p_chs =(unsigned char) ('0'+reminder);
            p_chs++;
        }
        else
        {
            printf("to_print的实际位数超出指定的bit位数！\n");
            exit(-1);
        }
    }
    p_chs=reset;
    //倒序打印,从bit位（空字符前一位）到 0位，因为字符串的有效部分是0到空字符前一位
    for(i= bit ; i >= 0;i--)
    {
        printf("%c",*(p_chs+i));
    }
    //printf("%s",p_chs);
    p_chs=reset;
   free(p_chs);
   p_chs = NULL;
   reset = NULL;
}

/****************************/

int main(int argc, char* argv[])
{
    bit_array tes;
    int i, j;
    
    tes = bitarray_create(CHAR_BIT*80);//创建一个包含8*800=640位的位数组
    
    if(tes !=NULL){
        //测试bitarray_max_bits函数     
        int max=bitarray_max_bits(tes);
        printf("max_bits=%ld\n",bitarray_max_bits(tes));
        printf("\n set \n");
        //把偶数位全部置为1，并将位数组打印出来
        for(i=0;i<max;i+=2)
            bitarray_set_bit(tes,i);
        for(j=0;j<max;j++)
            printf("%d",bitarray_test_bit(tes,j));//按64位每行打印
        printf("\n clear \n");
    //再把所有偶数位设置为0，再打印
        for(i=0;i<max;i+=2)
            bitarray_clear_bit(tes,i);
        for(j=0;j<max;j++)
            printf("%d",bitarray_test_bit(tes,j));//按64位每行打印
        printf("\n done \n");

        bitarray_destroy(tes);//别忘了销毁，不然就内存泄露了
        tes=NULL;
    }
    
    /****************************/
    
    //按指定的位数打印一个变量的位模式
    i=12138;
    printf("i %d\n", i);
    print_in_bitmode(i,16);
    
    printf("\n");
    
    return 0;
}