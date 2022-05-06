#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{ 
    FILE* fp;

    fp = fopen("file.txt", "w");
    fprintf(fp, "Hello %s %d", "world", 123456);

    fclose(fp);

    return 0;
}