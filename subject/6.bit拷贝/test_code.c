#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#define BITARRAY_SHIFT  (3)
#define BITARRAY_MASK   (0x7)

#define BITARRAY_BYTE_INDEX(num)        ((num) >> BITARRAY_SHIFT)
#define BITARRAY_B_SET(array, num)      (array[BITARRAY_BYTE_INDEX(num)] |= (0x80 >> ((num)&BITARRAY_MASK)))
#define BITARRAY_B_CLR(array, num)      (array[BITARRAY_BYTE_INDEX(num)] &= ~(0x80 >> ((num)&BITARRAY_MASK)))
#define BITARRAY_B_IS_IN(array, num)    (array[BITARRAY_BYTE_INDEX(num)] & (0x80 >> ((num)&BITARRAY_MASK)))


//已废弃
void copybit_1(unsigned char *dst_data, unsigned int dst_start_bit, unsigned char *src_data, unsigned int src_start_bit, unsigned int copy_bit_len)
{
    unsigned char src_mask_f, src_mask_b;

    unsigned char *src_ptr = src_data;
    unsigned char *dst_ptr = dst_data;
    
    unsigned char src_offset_num = 0;
    unsigned char dst_offset_num = 0;
    unsigned char src_dst_offset_num = 0;
    unsigned char inv_src_dst_offset_num = 0;
    
    unsigned int src_len;
    
    src_len = copy_bit_len / 8;

    src_mask_f = 0xff << (8 - (src_start_bit % 8));
    src_mask_b = ~src_mask_f;
    
    src_offset_num = 8 - src_start_bit % 8;
    dst_offset_num = 8 - dst_start_bit % 8;
    src_dst_offset_num = src_offset_num > dst_offset_num ? (src_offset_num - dst_offset_num) : (dst_offset_num - src_offset_num);
    inv_src_dst_offset_num = 8 - src_dst_offset_num;
    
    src_ptr = src_ptr + src_start_bit / 8;
    dst_ptr = dst_ptr + dst_start_bit / 8;
    
    if(src_len > 0)
    {
        src_len = src_len - 1;
        
        if(src_offset_num > dst_offset_num)
        {
            for(int i = 0; i < src_len; i++)
            {
                *dst_ptr = *dst_ptr | ((*src_ptr & src_mask_b) >> src_dst_offset_num);
                dst_ptr ++;
                *dst_ptr = *src_ptr << inv_src_dst_offset_num;
                src_ptr ++;
                *dst_ptr = *dst_ptr | ((*src_ptr & src_mask_f) >> src_dst_offset_num);
            }
            *dst_ptr = *dst_ptr | ((*src_ptr & src_mask_b) >> src_dst_offset_num);
        }
        else
        {
            for(int i = 0; i < src_len; i++)
            {
                *dst_ptr = *dst_ptr | ((*src_ptr & src_mask_b) << src_dst_offset_num);
                src_ptr ++;
                *dst_ptr = *dst_ptr | ((*src_ptr & src_mask_f) >> inv_src_dst_offset_num);
                dst_ptr ++;
                *dst_ptr = (*src_ptr & src_mask_f) << src_dst_offset_num;
            }
            *dst_ptr = *dst_ptr | ((*src_ptr & src_mask_b) << src_dst_offset_num);
            src_ptr ++;
            *dst_ptr = *dst_ptr | ((*src_ptr & src_mask_f) >> inv_src_dst_offset_num);
        }
    }
    
    for(int i = (src_start_bit + copy_bit_len - (dst_start_bit + copy_bit_len) % 8); i < src_start_bit + copy_bit_len; i++)
    {
        if (BITARRAY_B_IS_IN(src_data, i))
            BITARRAY_B_SET(dst_data, i + dst_start_bit - src_start_bit);
        else
            BITARRAY_B_CLR(dst_data, i + dst_start_bit - src_start_bit);
    }
}

//已废弃，可作为验证
void copybit_2(unsigned char *dst_data, unsigned int dst_start_bit, unsigned char *src_data, unsigned int src_start_bit, unsigned int copy_bit_len)
{
    for(int i = src_start_bit; i < src_start_bit + copy_bit_len; i++)
    {
        if (BITARRAY_B_IS_IN(src_data, i))
            BITARRAY_B_SET(dst_data, i + dst_start_bit - src_start_bit);
        else
            BITARRAY_B_CLR(dst_data, i + dst_start_bit - src_start_bit);
    }
}

//已废弃
void copybit_3(unsigned char *dst_data, unsigned int dst_start_bit, unsigned char *src_data, unsigned int src_start_bit, unsigned int copy_bit_len)
{
    unsigned char src_mask_f, src_mask_b;
    unsigned char dst_mask_f, dst_mask_b;

    unsigned char *src_ptr = src_data;
    unsigned char *dst_ptr = dst_data;
    
    unsigned char src_offset_num = 0;
    unsigned char dst_offset_num = 0;
    unsigned char src_dst_offset_num = 0;
    unsigned char inv_src_dst_offset_num = 0;
    
    unsigned char src_offset_f = 0, src_offset_b = 0;
    unsigned char dst_offset_f = 0, dst_offset_b = 0;
    
    unsigned int src_len;
    
    src_len = copy_bit_len / 8;

    src_mask_b = 0xff >> (src_start_bit % 8);
    src_mask_f = ~src_mask_b;

    dst_mask_b =  0xff >> (dst_start_bit % 8);
    dst_mask_f =  ~dst_mask_b;
    
    src_offset_f = src_start_bit % 8;
    src_offset_b = 8 - src_offset_f;
    
    dst_offset_f = dst_start_bit % 8;
    dst_offset_b = 8 - dst_offset_f;
    
    src_offset_num = 8 - src_start_bit % 8;
    dst_offset_num = 8 - dst_start_bit % 8;
    src_dst_offset_num = src_offset_num > dst_offset_num ? (src_offset_num - dst_offset_num) : (dst_offset_num - src_offset_num);
    inv_src_dst_offset_num = 8 - src_dst_offset_num;
    
    src_ptr = src_ptr + src_start_bit / 8;
    dst_ptr = dst_ptr + dst_start_bit / 8;
    
    if(src_len > 0)
    {
        src_len = src_len - 1;
        
        if(src_offset_num > dst_offset_num)
        {
            *dst_ptr = (*src_ptr & src_mask_b) >> src_dst_offset_num;
            dst_ptr++;
            
            for(int i = 0; i < src_len; i++)
            {
                *dst_ptr = *src_ptr << inv_src_dst_offset_num | *(src_ptr + 1) >> src_dst_offset_num;
                dst_ptr++;
                src_ptr++;
            }
            
            *dst_ptr = *src_ptr << inv_src_dst_offset_num | (*(src_ptr + 1) & src_offset_f) >> src_dst_offset_num;
        }
        else
        {
            *dst_ptr = (*src_ptr & src_mask_b) << src_dst_offset_num | *(src_ptr + 1) >> inv_src_dst_offset_num;
            dst_ptr++;
            src_ptr++;
            
            for(int i = 0; i < src_len; i++)
            {
                *dst_ptr = *src_ptr << src_dst_offset_num | *(src_ptr + 1) >> inv_src_dst_offset_num;
                dst_ptr++;
                src_ptr++;
            }
            
            *dst_ptr = (*src_ptr & src_mask_f) << src_dst_offset_num;
        }
    }
    
    for(int i = (src_start_bit + copy_bit_len - (dst_start_bit + copy_bit_len) % 8); i < src_start_bit + copy_bit_len; i++)
    {
        if (BITARRAY_B_IS_IN(src_data, i))
            BITARRAY_B_SET(dst_data, i + dst_start_bit - src_start_bit);
        else
            BITARRAY_B_CLR(dst_data, i + dst_start_bit - src_start_bit);
    }
}

//推荐使用
void copybit(unsigned char *dst_data, unsigned int dst_start_bit, unsigned char *src_data, unsigned int src_start_bit, unsigned int copy_bit_len)
{
    unsigned char src_mask_f, src_mask_b;
    unsigned char dst_mask_f, dst_mask_b;

    unsigned char *src_ptr = src_data;
    unsigned char *dst_ptr = dst_data;
    
    unsigned char src_offset_num = 0;
    unsigned char dst_offset_num = 0;
    unsigned char src_dst_offset_num = 0;
    unsigned char inv_src_dst_offset_num = 0;
    
    unsigned int src_len;
    
    src_len = copy_bit_len / 8;

    src_mask_b = 0xff >> (src_start_bit % 8);
    src_mask_f = ~src_mask_b;

    dst_mask_b =  0xff >> (dst_start_bit % 8);
    dst_mask_f =  ~dst_mask_b;
    
    src_offset_num = 8 - src_start_bit % 8;
    dst_offset_num = 8 - dst_start_bit % 8;
    src_dst_offset_num = src_offset_num > dst_offset_num ? (src_offset_num - dst_offset_num) : (dst_offset_num - src_offset_num);
    inv_src_dst_offset_num = 8 - src_dst_offset_num;
    
    src_ptr = src_ptr + src_start_bit / 8;
    dst_ptr = dst_ptr + dst_start_bit / 8;
    
    if(src_len > 0)
    {
        src_len = src_len - 1;
        
        if(src_offset_num > dst_offset_num)
        {
            *dst_ptr = (*dst_ptr & dst_mask_f) | (*src_ptr & src_mask_b) >> src_dst_offset_num;
            dst_ptr++;

            for (int i = 0; i < src_len; i++)
            {
                *dst_ptr = *src_ptr << inv_src_dst_offset_num | *(src_ptr + 1) >> src_dst_offset_num;
                dst_ptr++;
                src_ptr++;
            }

            *dst_ptr = (*dst_ptr & dst_mask_b) | ((*src_ptr << inv_src_dst_offset_num | (*(src_ptr + 1) & src_mask_f) >> src_dst_offset_num) & dst_mask_f);
        }
        else
        {
            *dst_ptr = (*dst_ptr & dst_mask_f) | (((*src_ptr & src_mask_b) << src_dst_offset_num | *(src_ptr + 1) >> inv_src_dst_offset_num) & dst_mask_b);
            dst_ptr++;
            src_ptr++;

            for (int i = 0; i < src_len; i++)
            {
                *dst_ptr = *src_ptr << src_dst_offset_num | *(src_ptr + 1) >> inv_src_dst_offset_num;
                dst_ptr++;
                src_ptr++;
            }

            *dst_ptr = (*dst_ptr & dst_mask_b) | (((*src_ptr & src_mask_f) << src_dst_offset_num) & dst_mask_f);
        }
    }
    
    for(int i = (src_start_bit + copy_bit_len - (copy_bit_len) % 8); i < (src_start_bit + copy_bit_len); i++)
    {
        if (BITARRAY_B_IS_IN(src_data, i))
            BITARRAY_B_SET(dst_data, i + dst_start_bit - src_start_bit);
        else
            BITARRAY_B_CLR(dst_data, i + dst_start_bit - src_start_bit);
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

char *itoa(int val, char *buf, unsigned radix)
{
    char        *p;
    char        *firstdig;
    char        temp;
    unsigned    digval;

    p = buf;
    if(val <0)
    {
        *p++ = '-';
        val = (unsigned long)(-(long)val);
    }
    firstdig = p; 
    do{
        digval = (unsigned)(val % radix);
        val /= radix;
        
        if  (digval > 9)
            *p++ = (char)(digval - 10 + 'a');
        else
            *p++ = (char)(digval + '0');
    }while(val > 0);

    *p-- = '\0';
    do{
        temp = *p;
        *p = *firstdig;
        *firstdig = temp;
        --p;
        ++firstdig;
    }while(firstdig < p);

    return buf;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    unsigned char DstData[20480];
    unsigned char SrcData[20480];
    struct  timeval tv_begin,tv_end;
    
    /*************************************************************************************************************/
    
    //拷贝速度验证
    memset(SrcData, 0xa5, sizeof(SrcData));
    memset(DstData, 0x00, sizeof(DstData));

    gettimeofday(&tv_begin,NULL);
    
    copybit_1(DstData, 6, SrcData, 3, 160000);

    gettimeofday(&tv_end,NULL);

    printf("tv_begin_sec:%ld\n", tv_begin.tv_sec);
    printf("tv_begin_usec:%ld\n", tv_begin.tv_usec);

    printf("tv_end_sec:%ld\n", tv_end.tv_sec);
    printf("tv_end_usec:%ld\n", tv_end.tv_usec);
    
    printf("run_time:%lds %ldus\n", (tv_end.tv_sec - tv_begin.tv_sec), (tv_end.tv_usec - tv_begin.tv_usec));

    /*************************************************************************************************************/
    
    //拷贝速度验证
    memset(SrcData, 0xa5, sizeof(SrcData));
    memset(DstData, 0x00, sizeof(DstData));
    
    gettimeofday(&tv_begin,NULL);
    
    copybit_2(DstData, 6, SrcData, 3, 160000);

    gettimeofday(&tv_end,NULL);

    printf("tv_begin_sec:%ld\n", tv_begin.tv_sec);
    printf("tv_begin_usec:%ld\n", tv_begin.tv_usec);

    printf("tv_end_sec:%ld\n", tv_end.tv_sec);
    printf("tv_end_usec:%ld\n", tv_end.tv_usec);
    
    printf("run_time:%lds %ldus\n", (tv_end.tv_sec - tv_begin.tv_sec), (tv_end.tv_usec - tv_begin.tv_usec));
    
    /*************************************************************************************************************/

    //拷贝速度验证
    memset(SrcData, 0xa5, sizeof(SrcData));
    memset(DstData, 0x00, sizeof(DstData));
    
    gettimeofday(&tv_begin,NULL);
    
    copybit_3(DstData, 6, SrcData, 3, 160000);

    gettimeofday(&tv_end,NULL);

    printf("tv_begin_sec:%ld\n", tv_begin.tv_sec);
    printf("tv_begin_usec:%ld\n", tv_begin.tv_usec);

    printf("tv_end_sec:%ld\n", tv_end.tv_sec);
    printf("tv_end_usec:%ld\n", tv_end.tv_usec);
    
    printf("run_time:%lds %ldus\n", (tv_end.tv_sec - tv_begin.tv_sec), (tv_end.tv_usec - tv_begin.tv_usec));
    
    /*************************************************************************************************************/
    
    //拷贝速度验证
    memset(SrcData, 0xa5, sizeof(SrcData));
    memset(DstData, 0x00, sizeof(DstData));
    
    gettimeofday(&tv_begin,NULL);
    
    copybit(DstData, 6, SrcData, 3, 160000);

    gettimeofday(&tv_end,NULL);

    printf("tv_begin_sec:%ld\n", tv_begin.tv_sec);
    printf("tv_begin_usec:%ld\n", tv_begin.tv_usec);

    printf("tv_end_sec:%ld\n", tv_end.tv_sec);
    printf("tv_end_usec:%ld\n", tv_end.tv_usec);
    
    printf("run_time:%lds %ldus\n", (tv_end.tv_sec - tv_begin.tv_sec), (tv_end.tv_usec - tv_begin.tv_usec));
    
    /*************************************************************************************************************/
    
    //拷贝效果验证
    char str[100];
    
    // memset(SrcData, 0xff, sizeof(SrcData));
    // memset(DstData, 0x00, sizeof(DstData));
    
    //copybit(DstData, 119, SrcData, 0, 9);
    
    //memset(SrcData, 0x5A, sizeof(SrcData));
    // memset(SrcData, 0xff, sizeof(SrcData));
    // memset(DstData, 0x00, sizeof(DstData));
    memset(SrcData, 0x00, sizeof(SrcData));
    memset(DstData, 0xff, sizeof(DstData));
    copybit(DstData, 100, SrcData, 0, 17);
    // CmnTypeCopyBit(DstData, 9, SrcData, 127, 64);

    //十六进制形式显示
    for(int i = 0; i < 32; i++)
        printf("0x%02x ", SrcData[i]);
    
    printf("\n");
    
    //二进制形式显示
    memset(str, 0x00, sizeof(str));
    for(int i = 0; i < 32; i++)
    {
        if(i % 8 == 0)
            printf("\n");
        
        itoa(SrcData[i], str, 2);
        
        int len = strlen(str);
        for(int j = 0; j < (8 - len); j++)
        {
            for(int k = 0; k < 8; k++)
            {
                str[7 - k + 1] = str[7 - k];
            }
            str[0] = '0';
        }
        
        str[8] = '\0';
        
        printf("%s ", str);
    }
    
    printf("\n");
    printf("\n");
    
    //十六进制形式显示
    for(int i = 0; i < 32; i++)
        printf("0x%02x ", DstData[i]);
    
    printf("\n");
    
    //二进制形式显示
    memset(str, 0x00, sizeof(str));
    for(int i = 0; i < 32; i++)
    {
        if(i % 8 == 0)
            printf("\n");
        
        itoa(DstData[i], str, 2);
        
        int len = strlen(str);
        for(int j = 0; j < (8 - len); j++)
        {
            for(int k = 0; k < 8; k++)
            {
                str[7 - k + 1] = str[7 - k];
            }
            str[0] = '0';
        }
        
        str[8] = '\0';
        
        printf("%s ", str);
    }
    
    printf("\n");

    return 0;
}

