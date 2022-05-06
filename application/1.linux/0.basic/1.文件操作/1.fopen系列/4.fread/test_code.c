#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    char c[] = "hello world";
    char buffer[20];

    /* 打开文件用于读写 */
    fp = fopen("file.txt", "w+");

    /* 写入数据到文件 */
    fwrite(c, 1, strlen(c) + 1, fp);

    /* 查找文件的开头 */
    fseek(fp, 0, SEEK_SET);

    /* 读取并显示数据 */
    fread(buffer, 1, strlen(c) + 1, fp);
    printf("%s\n", buffer);
    fclose(fp);

    return 0;
}