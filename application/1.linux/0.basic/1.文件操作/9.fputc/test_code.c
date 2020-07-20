#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    int ch;

    fp = fopen("file.txt", "w+");
    for(ch = 48; ch <= 58; ch++)
    {
        fputc(ch, fp);
    }
    fclose(fp);

    return 0;
}