#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int getSum(int a, int b){
    if (b == 0)
        return a;
    else
        return getSum( a ^ b, (unsigned int)(a & b) << 1);
}

int getSum2(int a, int b)
{
    return a == 0 ? b : getSum2((a & b) << 1, a ^ b);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int A = 0, B = 0;
    printf("Enter the two numbers to add\n");
    scanf("%d %d",&A,&B);
    printf("\nRequired sum is %d\n",getSum(A,B));
    printf("\nRequired sum is %d\n",getSum2(A,B));
    
    return 0;
}