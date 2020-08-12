#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define buf_size 1024

typedef struct rc4_key
{ 
    unsigned char state[256]; 
    unsigned char x; 
    unsigned char y;
} rc4_key;

void swap_byte(unsigned char*x, unsigned char*y)
{
    *x=*x^*y;
    *y=*x^*y;
    *x=*x^*y;
}

void prepare_key(unsigned char *key_data_ptr, int key_data_len, rc4_key *key)
{
    int i;
    unsigned char t;
    unsigned char swapByte;
    unsigned char index1;
    unsigned char index2;
    unsigned char* state;
    short counter;
    
    state = &key->state[0];
    
    for(counter = 0; counter < 256; counter++)
        state[counter] = counter;
    
    key->x = 0;
    key->y = 0;
    index1 = 0;
    index2 = 0;
    
    for(counter = 0; counter < 256; counter++)
    {
        index2 = (key_data_ptr[index1] + state[counter] + index2) % 256;
        swap_byte(&state[counter], &state[index2]);
        index1 = (index1 + 1) % key_data_len;
    }
}
void rc4(unsigned char *buffer_ptr, int buffer_len, rc4_key *key)
{
    unsigned char t;
    unsigned char x;
    unsigned char y;
    unsigned char* state;
    unsigned char xorIndex;
    short counter;
    
    x = key->x;
    y = key->y;
    state = &key->state[0];
    
    for(counter = 0; counter < buffer_len; counter++)
    {
        x = (x + 1) % 256;
        y = (state[x] + y) % 256;
        swap_byte(&state[x], &state[y]);
        xorIndex = (state[x] + state[y]) % 256;
        buffer_ptr[counter] ^= state[xorIndex];
    }
    
    key->x = x;
    key->y = y;
}


/****************************/

int main(int argc, char* argv[])
{
    struct rc4_key key;
    unsigned char seed[] = "1234";
    unsigned char myinput[100] = "hello world!";
    int i = 0, len = 0;
    
    printf("orignal text:%s\n",myinput);
    
    memset(&key, 0, sizeof(key));
    
    len = strlen(myinput);
    
    //加密
    prepare_key(seed, 4, &key);
    rc4(myinput, len, &key);
    printf("secret string:");
    for(i = 0; i < len; i++)
    {
        printf("0x%x ",myinput[i]);
    }
    printf("\ndecrypt the secret string,the result is:");
    
    memset(&key, 0, sizeof(key));
    
     //解密
    prepare_key(seed, 4, &key);
    rc4(myinput, len, &key);
    printf("%s\n", myinput);
    
    return 0;
}