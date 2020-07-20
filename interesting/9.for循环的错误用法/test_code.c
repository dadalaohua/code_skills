#include <stdio.h>

int main(int argc, char* argv[])
{
    int arr[] = {5, 4, 3, 2, 1};
    int i = -1;
    
    for(i = -1; i < sizeof(arr)/sizeof(int) - 1; i++)
    {
        printf("%d\n",arr[i+1]);
    }
    
    printf("end\n");

    return 0;
}