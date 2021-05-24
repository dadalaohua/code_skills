#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
void comb_sort(int arr[], int len) {
    double shrink_factor = 0.8;
    int gap = len, swapped = 1, i;
    int temp;
    while (gap > 1 || swapped) {
        if (gap > 1)
            gap *= shrink_factor;
        swapped = 0;
        for (i = 0; gap + i < len; i++)
            if (arr[i] > arr[i + gap]) {
                temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = 1;
            }
    }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int i, buf[10] = {2,5,6,3,-7,8,0,9,12,1};
    
    printf("The orginal data array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]);
        
    comb_sort(buf, 10);
    
    printf("\nThe result of sorting for the array is\n");
    for(i = 0; i < 10; i++)
        printf("%d ",buf[i]); 
    
    printf("\n");
    
    return 0;
}