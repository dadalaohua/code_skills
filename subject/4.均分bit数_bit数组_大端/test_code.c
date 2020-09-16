#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE         48
#define SPLIT_BUFF_SIZE   6

/************************************************************************/
/*                                                                      */
/************************************************************************/

#define BITARRAY_SHIFT  3
#define BITARRAY_MASK   0x7
 
#define BITARRAY_SIZE(size)             ((size >> BITARRAY_SHIFT) + 1)
#define BITARRAY_BYTE_INDEX(num)        (num >> BITARRAY_SHIFT)
#define BITARRAY_B_SET(array, num)        (array[BITARRAY_BYTE_INDEX(num)] |= (0x80 >> (num & BITARRAY_MASK)))
#define BITARRAY_B_CLR(array, num)        (array[BITARRAY_BYTE_INDEX(num)] &= ~(0x80 >> (num & BITARRAY_MASK)))
#define BITARRAY_B_IS_IN(array, num)      (array[BITARRAY_BYTE_INDEX(num)] & (0x80 >> (num & BITARRAY_MASK)))
#define BITARRAY_BYTE_BIT_NUM(data)     ({ data = (data & 0x55) + ((data >> 1) & 0x55);\
                                           data = (data & 0x33) + ((data >> 2) & 0x33);\
                                           data = (data & 0x0f) + ((data >> 4) & 0x0f); })
#define BITARRAY_ARRAY_BIT_NUM(array, size)     ({ unsigned int i, count;\
                                                    for(i = 0; i < BITARRAY_SIZE(size); i++)\
                                                        count += BITARRAY_BYTE_BIT_NUM(array[i]);\
                                                        count;\
                                                        })

/************************************************************************/
/*                                                                      */
/************************************************************************/

unsigned char buff[BUFF_SIZE];
unsigned char split_buff[SPLIT_BUFF_SIZE * BUFF_SIZE];

static inline unsigned int count_bit(unsigned char data)
{
    unsigned int count = 0;
    
    while(data)
    {
       data &= (data - 1);
       count ++;
    }
    
    return count;
}

unsigned int count_buff_bit(unsigned char *data, unsigned int len)
{
    unsigned int count = 0;;
    int i;
    
    for(i = 0; i < len; i++)
    {
        count += count_bit(data[i]);
    }
    
    return count;
}

void data_split_bit(unsigned char* src, unsigned int src_len, unsigned char* dst, unsigned int split_count)
{
    unsigned int sum, avg_cnt;
    unsigned char* ptr = dst;
    unsigned int count = 0, offset = 0;
    int i;
    
    sum = count_buff_bit(src, src_len);
    
    avg_cnt = sum/split_count;
    
    for(i = 0; i < src_len * 8; i++)
    {
        if(BITARRAY_B_IS_IN(src, i))
        {
            BITARRAY_B_SET(ptr, i);
            count++;
            
            if(count > avg_cnt && offset < (split_count - 1))
            {
                count = 0;
                offset ++;
                ptr = dst + offset * src_len;
            }
        }
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int rab1(int a, int b, int *r)
{ 
    int k,l,m,i,p;
    
    k = b-a+1;
    l = 2;
    
    while(l<k)
        l=l+l;
    
    m=4*l;
    k=*r;
    i=1;
    
    while(i<=1)
    {
        k=k+k+k+k+k;
        k=k%m;
        l=k/4+a;
        
        if (l<=b)
        {
            p=l;
            i=i+1;
        }
    }
    *r=k;
    
    return(p);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i,j,r;
    unsigned char data_temp = 0;
    
    r = 8;
    
    for(i = 0; i < BUFF_SIZE; i++)
    {
        buff[i] = rab1(0, 255, &r);
    }
    
    //memset(buff, 0x3f, 1);
    // memset(buff, 1, 7);
    // memset(buff+36, 5, 12);
    // memset(buff+12, 7, 3);
    
    for(i = 0; i < BUFF_SIZE; i++)
    {
        if(i%BUFF_SIZE == 0)
            printf("\n");
        
        printf("0x%x ", buff[i]);
    }
    printf("\n");
    
    
    memset(split_buff, 0, sizeof(split_buff));
    data_split_bit(buff, sizeof(buff), split_buff, SPLIT_BUFF_SIZE);
    
    printf("\n");
    for(i = 0; i < SPLIT_BUFF_SIZE * BUFF_SIZE; i++)
    {
        if(i%BUFF_SIZE == 0)
            printf("\n");
        
        printf("0x%x ", split_buff[i]);
    }
    printf("\n");
    
    printf("\n");
    for(i = 0; i < SPLIT_BUFF_SIZE; i++)
    {
        printf("%d ", count_buff_bit(split_buff + i * BUFF_SIZE, BUFF_SIZE));
    }
    printf("\n");
    
    for(i = 0; i < BUFF_SIZE; i++)
    {
        if(i%BUFF_SIZE == 0)
            printf("\n");
        
        data_temp = 0;
        
        for(j = 0; j < SPLIT_BUFF_SIZE; j++)
        {
            data_temp |= split_buff[i + j * BUFF_SIZE];
        }
        
        printf("0x%x ", data_temp);
        
        if(data_temp != buff[i])
        {
            printf("data split error\n");
        }
    }
    printf("\n");
    printf("data split success\n");
    

    return 0;
}