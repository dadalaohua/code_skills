#include <stdio.h>
#include <stdlib.h>

#define INT_MAX ((int)(~0U>>1))

const static int Fib[47 + 1] =
{ 
    0,  1,  1,  2,  3,  5,  8,  13,  21,  34,  55,  89,  144,  233,  377,  610,  987,  1597,  2584,  4181,  6765,
    10946,  17711,  28657,  46368,  75025,  121393,  196418,  317811,  514229,  832040,  1346269,  2178309,  3524578,
    5702887,  9227465,  14930352,  24157817,  39088169,  63245986,  102334155,  165580141,  267914296,
    433494437,  701408733,  1134903170,  1836311903, INT_MAX
};

int fibonacci_search(int *buf, int len, int key)
{
    int k, idx, offs; 
    int f0, f1, t;
    
    for(f0 = 0, f1 = 1, k = 1; f1 < len; t = f1, f1 += f0, f0 = t, ++k);

    for(offs =  0; k >  0;  )
    {
        idx = offs + Fib[--k];

        /* note that at this point k  has already been decremented once */
        if(idx >= len || key < buf[idx])  // index out of bounds or key in 1st part
        {
             continue;
        }
        else if (key > buf[idx])
        {
            // key in 2nd part
            offs = idx;
            --k;
        }
        else  // key==buf[idx], found
            return idx;
    }

    return -1;
}

/****************************/

int main(int argc, char* argv[])
{
    int a[] = {1,2,3,4,5,6,7,8,9,12,13,45,67,89,99,101,111,123,134,565,677};
    int b[] = {677, 1, 7, 11, 67, 99, 1, 680};

    int i;
    
    for(i = 0; i<sizeof(b)/sizeof(b[0]); i++ )
    {
        printf("%d\n", fibonacci_search(a, sizeof(a)/sizeof(a[0]), b[i]));
    }
    
    return 0;
}
