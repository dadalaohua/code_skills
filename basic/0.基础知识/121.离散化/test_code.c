#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
int compare(const void* a, const void* b)
{
    return ( *(int *)a - *(int *)b );
}

void discretization(int* nums, int numsSize)
{
    int* buf = malloc(sizeof(int) * numsSize);
    memcpy(buf, nums, sizeof(int) * numsSize);
    qsort(buf, numsSize, sizeof(int), compare);
    
    int cnt = 0;
    buf[cnt++] = buf[0];
    for(int i = 1; i < numsSize; i++) {
        if(buf[cnt - 1] != buf[i])
            buf[cnt++] = buf[i];
    }
    
    for(int i = 0; i < numsSize; i++) {
        int left = 0, right = cnt - 1;
        int mid;
        while(left <= right) {
            mid = left + (right - left) / 2;
            if(buf[mid] < nums[i]) {
                left = mid + 1;
            } else if(buf[mid] > nums[i]) {
                right = mid - 1;
            } else {
                nums[i] = mid + 1;
                break;
            }
        }
    }
    
    return;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int nums[] = {8, 24, 55, 6, -30, 6, 63, 100, 6, 63};
    
    for(int i = 0; i < sizeof(nums)/sizeof(int); i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");
    
    discretization(nums, sizeof(nums)/sizeof(int));
    
    for(int i = 0; i < sizeof(nums)/sizeof(int); i++) {
        printf("%d, ", nums[i]);
    }
    printf("\n");
    
    return 0;
}