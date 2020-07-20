#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{ 
    FILE * fp;

    fp = fopen("file.txt", "w+");
    fprintf(fp, "%s %s %s %d", "We", "are", "in", 2014);

    fclose(fp);

    return 0;
}