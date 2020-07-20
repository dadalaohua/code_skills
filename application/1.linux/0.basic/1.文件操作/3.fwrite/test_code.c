#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{ 
    FILE *fp;
    char str[] = "hello world";

    fp = fopen( "file.txt" , "w" );
    fwrite(str, sizeof(str) , 1, fp);

    fclose(fp);

    return 0;
}