#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;

    fp = fopen("file.txt", "w+");

    fputs("hello ", fp);
    fputs("world", fp);

    fclose(fp);

    return 0;
}