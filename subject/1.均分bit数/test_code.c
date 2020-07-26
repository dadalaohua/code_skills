#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE         48
#define SPLIT_BUFF_SIZE   6

unsigned char buff[BUFF_SIZE];
unsigned char split_buff[SPLIT_BUFF_SIZE * BUFF_SIZE];

static inline unsigned int count_bit1(unsigned char data)
{
    unsigned int count = 0;
    
    while(data)
    {
       data &= (data - 1);
       count ++;
    }
    
    return count;
}

unsigned int count_bit(unsigned char *data, unsigned int len)
{
    unsigned int count = 0;;
    int i;
    
    for(i = 0; i < len; i++)
    {
        count += count_bit1(data[i]);
    }
    
    return count;
}

void data_split_bit(unsigned char* src, unsigned int src_len, unsigned char* des, unsigned int split_count)
{
    unsigned int sum, avg_cnt;
    unsigned int locat, start_locat;
    unsigned char buff_split_f, buff_split_b;
    
    int i, j;
    
    sum = 0;
    
    for(i = 0; i < 48; i++)
    {
        if(i%48 == 0)
            printf("\n");
        
        printf("%d ", count_bit1(src[i]));
    }
    printf("\n");
    
    sum = count_bit(src, src_len);
    
    avg_cnt = sum/split_count;
    
    printf("sum %d avg_cnt %d\n", sum, avg_cnt);
    
    locat  = 0;
    start_locat = 0;
    buff_split_f = 0;
    buff_split_b = 0;
    
    for(i = 0; i < split_count; i++)
    {
        unsigned int count = 0;
        unsigned int offset = 0;
        unsigned int count_temp = 0;
        
        if(i == (split_count - 1))
        {
            avg_cnt = sum - avg_cnt * (split_count - 1);
        }
        
        if(locat >= src_len)
            break;
        
        if(buff_split_b)
        {
            count = count_bit1(buff_split_b);
            if(count > avg_cnt)
            {
                buff_split_f = 0;
                
                for(j = 0; j < 8; j++)
                {
                    if(buff_split_b & (0x80 >> j))
                        buff_split_f |= (0x80 >> j);
                    
                    if(avg_cnt == count_bit1(buff_split_f))
                    {
                        buff_split_b = buff_split_b^buff_split_f;
                        break;
                    }
                }
                memcpy(des + i*src_len + start_locat - 1, &buff_split_f, 1);
                
                count = avg_cnt;
            }
            else
            {
                memcpy(des + i*src_len + start_locat - 1, &buff_split_b, 1);
                buff_split_b = 0;
            }
        }
        
        while(count < avg_cnt)
        {
            count_temp = count_bit1(src[locat]);
            locat ++;
            offset++;
            
            if((count + count_temp) > avg_cnt)
            {
                int cnt;
                unsigned char buff_tmp;
                
                cnt = avg_cnt - count;
                buff_tmp = src[locat - 1];
                
                buff_split_f = 0;
                
                for(j = 0; j < 8; j++)
                {
                    if(buff_tmp & (0x80 >> j))
                        buff_split_f |= (0x80 >> j);
                    
                    if(cnt == count_bit1(buff_split_f))
                    {
                        buff_split_b = buff_tmp^buff_split_f;
                        break;
                    }
                }
                
                memcpy(des + i*src_len + start_locat, src + start_locat, offset - 1);
                memcpy(des + i*src_len + start_locat + offset - 1, &buff_split_f, 1);
                
                break;
            }
            else if((count + count_temp) == avg_cnt)
            {
                memcpy(des + i*src_len + start_locat, src + start_locat, offset);
                break;
            }
            
            count += count_temp;
            
            if(locat >= src_len)
                break;
        }
        
        printf("i:%d count:%d locat:%d offset:%d\n", i, count, locat, offset);
        
        start_locat += offset;

        printf("start_locat %d, sum %d avg_cnt %d\n", start_locat, sum, avg_cnt);
    }
}

void data_split(void)
{
    unsigned int count, sum, avg_cnt, divisor;
    unsigned int locat, start_locat, offset;
    unsigned int buff_cnt[48];
    int i, j;
    
    sum = 0;
    
    for(i = 0; i < 48; i++)
    {
        buff_cnt[i] = count_bit1(buff[i]);
        sum += buff_cnt[i];
        
        if(i%48 == 0)
            printf("\n");
        
        printf("%d ", buff_cnt[i]);
    }
    printf("\n");
    
    avg_cnt = sum/6;
    
    printf("sum %d avg_cnt %d\n", sum, avg_cnt);
    
    locat  = 0;
    start_locat = 0;
    
    for(i = 0; i < 6; i++)
    {
        count = 0;
        offset = 0;
        
        if(locat < 48)
        {
            while(count < avg_cnt)
            {
                count += buff_cnt[locat];
                locat ++;
                offset++;
                
                if(locat >= 48)
                    break;
            }
            
            if(count > avg_cnt)
            {
                locat --;
                offset--;
                count -= buff_cnt[locat];
            }
            
            printf("i:%d count:%d locat:%d offset:%d\n", i, count, locat, offset);
        }
        
        memcpy(split_buff + i*48 + start_locat, buff + start_locat, offset);
        
        start_locat += offset;
        
        sum -= count;
        divisor = 6 - (i + 1);
        if(divisor)
            avg_cnt = sum/divisor;
        
        printf("start_locat %d, sum %d avg_cnt %d\n", start_locat, sum, avg_cnt);
    }
}

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
    
    // memset(split_buff, 0, sizeof(split_buff));
    // data_split();
    
    // printf("\n");
    // for(i = 0; i < 6 * 48; i++)
    // {
        // if(i%48 == 0)
            // printf("\n");
        
        // printf("0x%x ", split_buff[i]);
    // }
    // printf("\n");
    
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
        printf("%d ", count_bit(split_buff + i * BUFF_SIZE, BUFF_SIZE));
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