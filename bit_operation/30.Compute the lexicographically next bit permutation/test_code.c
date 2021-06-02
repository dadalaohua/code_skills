#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
unsigned int lexicographically_next_bit_permutation(unsigned int v)
{
    // unsigned int v; // current permutation of bits 
    unsigned int w; // next permutation of bits

    unsigned int t = v | (v - 1); // t gets v's least significant 0 bits set to 1
    // Next set to 1 the most significant bit to change, 
    // set to 0 the least significant ones, and add the necessary 1 bits.
    w = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));

    return w;
}

unsigned int lexicographically_next_bit_permutation_2(unsigned int v)
{
    // unsigned int v; // current permutation of bits 
    unsigned int w; // next permutation of bits

    unsigned int t = (v | (v - 1)) + 1;  
    w = t | ((((t & -t) / (v & -v)) >> 1) - 1);
    
    return w;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

char *itoa(int val, char *buf, unsigned radix)
{
    char   *p;
    char   *firstdig;
    char   temp;
    unsigned   digval;
    p = buf;
    if(val < 0)
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

int main(int argc, char* argv[])
{
    unsigned int val = 0x13;
    unsigned int val_tmp = 0x13;
    int i = 0;
    char s1[10], s2[10];
    
    for(i = 0; i < 32; i++)
    {
        val_tmp = lexicographically_next_bit_permutation(val);
        printf("0x%x 0x%x\n", val, val_tmp);
        itoa(val, s1, 2);
        itoa(val_tmp, s2, 2);
        printf("0b%s 0b%s\n", s1, s2);
        val = val_tmp;
    }
    
    printf("\n");
    printf("\n");
    printf("\n");
    
    val = 0x13;
    for(i = 0; i < 32; i++)
    {
        val_tmp = lexicographically_next_bit_permutation(val);
        printf("0x%x 0x%x\n", val, val_tmp);
        itoa(val, s1, 2);
        itoa(val_tmp, s2, 2);
        printf("0b%s 0b%s\n", s1, s2);
        val = val_tmp;
    }
    
    return 0;
}