#include <stdio.h>
#include <stdlib.h>

/****************************/

int main(int argc, char* argv[])
{
    int i,j,k;
    printf("There are different methods for TOM to distribute his books to  A,B,C\n");
    
    for(i = 1; i <= 5; i++)
        for(j = 1; j <= 5; j++)
            for(k = 1; k <= 5; k++)
                if(i!=j && j!=k && i!=k){
                    printf("(%d,%d,%d) ", i, j, k);    /*输出一种借书方案*/
                    }
    
    printf("\n");
    
    return 0;
}
