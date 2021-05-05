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

int main(int argc, char* argv[])
{
    unsigned char DstData[20480];
    unsigned char SrcData[20480];
    struct  timeval tv_begin,tv_end;
    
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

    return 0;
}

