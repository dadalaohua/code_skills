#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;

    fp = fopen("file.txt","w+");
    fputs("This is test code", fp);

    fseek(fp, 7, SEEK_SET);
    fputs(" C Programming Langauge", fp);
    fclose(fp);

    return 0;
}