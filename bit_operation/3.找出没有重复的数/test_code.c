#include <stdio.h>

int find(int* arr, int len){
    int tmp = arr[0];
    int i;
    
    for(i = 1;i < len; i++){
        tmp = tmp ^ arr[i];
    }
    return tmp;
}

int main(int argc, char* argv[])
{ 
    int buf[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    int num;
    
    num = find(buf, sizeof(buf)/sizeof(int));
    
    printf("num: %d\n", num);
    
    return 0;
}