#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{ 
    FILE *fp;
    char str[] = "hello world";

    fp = fopen( "file.txt" , "w" );
    fwrite(str, 1, sizeof(str), fp);

    fclose(fp);

    return 0;
}