#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STORAGE_PATH "./filetest"
/************************************************************************/
/*                                                                      */
/************************************************************************/
int fs_fputs_common_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);
    
    //写入内容
    char newbuf[64] = "helloworld";
    int ret = fputs(newbuf, newfp);
    if(ret < 0) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    printf("fputs ret %d buf %s\n", ret, newbuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件开头
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    if(fgets(readbuf, 64, newfp) == NULL) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    printf("fgets %s\n", readbuf);
    
    fclose(newfp);
    
    //比较内容
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

static void fs_fputs_test(void *priv)
{
    fs_fputs_common_test();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int fs_fgets_common_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);
    
    //写入内容
    char newbuf[64] = "helloworld";
    int ret = fputs(newbuf, newfp);
    if(ret < 0) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    printf("fputs ret %d buf %s\n", ret, newbuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件开头
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    if(fgets(readbuf, 64, newfp) == NULL) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    printf("fgets %s\n", readbuf);
    
    fclose(newfp);
    
    //比较内容
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

static void fs_fgets_test(void *priv)
{
    fs_fgets_common_test();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int fs_fputc_common_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);
    
    //写入内容
    char newbuf[64] = "helloworld";
    //int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    int newlen = 0;
    for(int i = 0; i < strlen(newbuf); i++) {
        fputc(newbuf[i], newfp);
        newlen++;
    }
    
    printf("fputc len %d %s\n", newlen, newbuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件开头
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = 0;
    do {
        char c = fgetc(newfp);
        if(feof(newfp)) {
            break;
        }
        readbuf[newlen++] = c;
    } while(1);
    printf("fgetc len %d %s\n", newlen, readbuf);
    
    fclose(newfp);
    
    //比较内容
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

static void fs_fputc_test(void *priv)
{
    fs_fputc_common_test();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int fs_fgetc_common_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);
    
    //写入内容
    char newbuf[64] = "helloworld";
    //int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    int newlen = 0;
    for(int i = 0; i < strlen(newbuf); i++) {
        fputc(newbuf[i], newfp);
        newlen++;
    }
    
    printf("fputc len %d %s\n", newlen, newbuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件开头
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = 0;
    do {
        char c = fgetc(newfp);
        if(feof(newfp)) {
            break;
        }
        readbuf[newlen++] = c;
    } while(1);
    printf("fgetc len %d %s\n", newlen, readbuf);
    
    fclose(newfp);
    
    //比较内容
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

static void fs_fgetc_test(void *priv)
{
    fs_fgetc_common_test();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int fs_ftell_common_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件末尾
    fseek(newfp, 0, SEEK_END);
    //获取当前文件位置
    int len = ftell(newfp);
    if(len != strlen(newbuf)) {
        printf("len %d\n", len);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件开头
    fseek(newfp, 0, SEEK_SET);
    //获取当前文件位置
    len = ftell(newfp);
    if(len != 0) {
        printf("len %d\n", len);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件开头向后偏移5的位置
    fseek(newfp, 5, SEEK_SET);
    //获取当前文件位置
    len = ftell(newfp);
    if(len != 5) {
        printf("len %d\n", len);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fclose(newfp);
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

static void fs_ftell_test(void *priv)
{
    fs_ftell_common_test();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int fs_fread_int_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);
    
    //写入内容
    int newbuf[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int newlen = fwrite(newbuf, sizeof(int), sizeof(newbuf)/sizeof(int), newfp);
    printf("fwrite len %d\n", newlen);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件开头
    fseek(newfp, 0, SEEK_SET);
    
    int readbuf[64] = {0};
    newlen = fread(readbuf, sizeof(int), sizeof(readbuf)/sizeof(int), newfp);
    printf("fread len %d\n", newlen);
    fclose(newfp);
    
    //比较内容
    for(int i = 0; i < newlen; i++) {
        if(readbuf[i] != newbuf[i]) {
            printf("readbuf[%d] = %d newbuf[%d] = %d\n", i, readbuf[i], i, newbuf[i]);
            printf("%s %d failed\n", __func__, __LINE__);
            return -1;
        }
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

int fs_fread_common_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);
    
    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件开头
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //比较内容
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

static void fs_fread_test(void *priv)
{
    fs_fread_common_test();
    fs_fread_int_test();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
int fs_fwrite_int_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);
    
    //写入内容
    int newbuf[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int newlen = fwrite(newbuf, sizeof(int), sizeof(newbuf)/sizeof(int), newfp);
    printf("fwrite len %d\n", newlen);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件开头
    fseek(newfp, 0, SEEK_SET);
    
    int readbuf[64] = {0};
    newlen = fread(readbuf, sizeof(int), sizeof(readbuf)/sizeof(int), newfp);
    printf("fread len %d\n", newlen);
    fclose(newfp);
    
    //比较内容
    for(int i = 0; i < newlen; i++) {
        if(readbuf[i] != newbuf[i]) {
            printf("readbuf[%d] = %d newbuf[%d] = %d\n", i, readbuf[i], i, newbuf[i]);
            printf("%s %d failed\n", __func__, __LINE__);
            return -1;
        }
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

int fs_fwrite_common_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);
    
    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件开头
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //比较内容
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

static void fs_fwrite_test(void *priv)
{
    fs_fwrite_common_test();
    fs_fwrite_int_test();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
/**
  * @brief      fseek SEEK_END 测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       SEEK_END : 文件的末尾。
  */
int fs_fseek_end_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件末尾
    fseek(newfp, 0, SEEK_END);
    //获取当前文件位置
    int len = ftell(newfp);
    if(len != strlen(newbuf)) {
        printf("len %d\n", len);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fseek SEEK_CUR 测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       SEEK_CUR : 文件指针的当前位置。
  */
int fs_fseek_cur_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);
    //获取当前文件位置
    int len = ftell(newfp);
    if(len != 0) {
        printf("len %d\n", len);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    
    //重新定位，当前在文件末尾，向前偏移 5
    fseek(newfp, -5, SEEK_CUR);
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    
    if(strcmp(readbuf, "world")) {
        printf("readbuf %s\n", readbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);
    //基于当前定位向后偏移5的位置
    fseek(newfp, 5, SEEK_CUR);
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    
    if(strcmp(readbuf, "world")) {
        printf("readbuf %s\n", readbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fclose(newfp);
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fseek SEEK_SET 测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       SEEK_SET : 文件的开头。
  */
int fs_fseek_set_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到文件头
    fseek(newfp, 0, SEEK_SET);
    
    //获取当前文件位置
    int len = ftell(newfp);
    if(len != 0) {
        printf("len %d\n", len);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到开头
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //定位到从起始位置开始偏移5的位置
    fseek(newfp, 5, SEEK_SET);
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, newbuf + 5)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf + 5);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fseek 测试
  *
  */
static void fs_fseek_test(void *priv)
{
    fs_fseek_set_test();
    fs_fseek_cur_test();
    fs_fseek_end_test();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
/**
  * @brief      fopen 模式"ab+"测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       模式"ab+":读写打开一个二进制文件，允许读或在文件末追加数据。
  */
int fs_fopen_abplus_test(void)
{
    printf("%s test\n", __func__);
    
    //打开一个用于读取和追加的文件
    FILE *newfp = fopen(STORAGE_PATH, "ab+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //追加到一个文件。写操作向文件末尾追加数据。如果文件不存在，则创建文件。
    newfp = fopen(STORAGE_PATH, "ab+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //输出当前文件位置
    printf("ftell len %zu\n", ftell(newfp));
    
    char writebuf[64] = "testwrite";
    newlen = fwrite(writebuf, 1, strlen(writebuf), newfp);
    printf("fwrite len %d %s\n", newlen, writebuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, "helloworldtestwrite")) {
        printf("readbuf %s\n", readbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //进行读测试
    newfp = fopen(STORAGE_PATH, "ab+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //输出当前文件位置
    printf("ftell len %zu\n", ftell(newfp));
    fseek(newfp, 0, SEEK_SET);
    //输出当前文件位置
    printf("ftell len %zu\n", ftell(newfp));
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    if(newlen == 0) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    fclose(newfp);
    
    if(strcmp(readbuf, "helloworldtestwrite")) {
        printf("readbuf %s\n", readbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fopen 模式"a+"测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       模式"a+":以附加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。 （原来的EOF符不保留）
  */
int fs_fopen_aplus_test(void)
{
    printf("%s test\n", __func__);
    
    //打开一个用于读取和追加的文件
    FILE *newfp = fopen(STORAGE_PATH, "a+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //追加到一个文件。写操作向文件末尾追加数据。如果文件不存在，则创建文件。
    newfp = fopen(STORAGE_PATH, "a+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //输出当前文件位置
    printf("ftell len %zu\n", ftell(newfp));
    
    char writebuf[64] = "testwrite";
    newlen = fwrite(writebuf, 1, strlen(writebuf), newfp);
    printf("fwrite len %d %s\n", newlen, writebuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    // for(int i = 0; i < sizeof(readbuf); i++) {
        // printf("%d %d(%c)\n", i, readbuf[i], readbuf[i]);
    // }
    fclose(newfp);
    
    if(strcmp(readbuf, "helloworldtestwrite")) {
        printf("readbuf %s\n", readbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //进行读测试
    newfp = fopen(STORAGE_PATH, "a+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //输出当前文件位置
    printf("ftell len %zu\n", ftell(newfp));
    fseek(newfp, 0, SEEK_SET);
    //输出当前文件位置
    printf("ftell len %zu\n", ftell(newfp));
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    if(newlen == 0) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    fclose(newfp);
    
    if(strcmp(readbuf, "helloworldtestwrite")) {
        printf("readbuf %s\n", readbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fopen 模式"a"测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       模式"a":以附加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。（EOF符保留）
  */
int fs_fopen_a_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 追加到一个文件。写操作向文件末尾追加数据。如果文件不存在，则创建文件。
    FILE *newfp = fopen(STORAGE_PATH, "a");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //追加到一个文件。写操作向文件末尾追加数据。如果文件不存在，则创建文件。
    newfp = fopen(STORAGE_PATH, "a");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //输出当前文件位置
    printf("ftell len %zu\n", ftell(newfp));
    
    char writebuf[64] = "testwrite";
    newlen = fwrite(writebuf, 1, strlen(writebuf), newfp);
    printf("fwrite len %d %s\n", newlen, writebuf);
    fclose(newfp);
    
    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    // for(int i = 0; i < sizeof(readbuf); i++) {
        // printf("%d %d(%c)\n", i, readbuf[i], readbuf[i]);
    // }
    fclose(newfp);
    
    if(strcmp(readbuf, "helloworldtestwrite")) {
        printf("readbuf %s\n", readbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //进行读测试
    newfp = fopen(STORAGE_PATH, "a");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //输出当前文件位置
    printf("ftell len %zu\n", ftell(newfp));
    fseek(newfp, 0, SEEK_SET);
    //输出当前文件位置
    printf("ftell len %zu\n", ftell(newfp));
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    if(newlen != 0) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    fclose(newfp);
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fopen 模式"rw+"测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       模式"rw+":读写打开一个文本文件，允许读和写。
  */
int fs_fopen_rwplus_test(void)
{
    printf("%s test\n", __func__);
    
    //文件不存在的情况下，打开
    FILE *newfp = fopen(STORAGE_PATH, "rw+");
    if(newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //新建文件 创建一个用于读写的空文件
    newfp = fopen(STORAGE_PATH, "w+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "rw+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //比较内容
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }

    //修改内容
    newfp = fopen(STORAGE_PATH, "rw+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    fseek(newfp, 2, SEEK_SET);
    newlen = fwrite(newbuf, 1, 2, newfp);
    printf("fwrite len %d\n", newlen);

    //获取修改后的内容
    fseek(newfp, 0, SEEK_SET);
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, "heheoworld")) {
        printf("readbuf %s\n", readbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fopen 模式"rb+"测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       模式"rb+":以可读写方式打开文件，该文件必须存在。
  */
int fs_fopen_rbplus_test(void)
{
    printf("%s test\n", __func__);
    
    //文件不存在的情况下，打开
    FILE *newfp = fopen(STORAGE_PATH, "rb+");
    if(newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //新建文件 创建一个用于读写的空文件
    newfp = fopen(STORAGE_PATH, "w+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "rb+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //比较内容
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }

    //修改内容
    newfp = fopen(STORAGE_PATH, "rb+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    fseek(newfp, 2, SEEK_SET);
    newlen = fwrite(newbuf, 1, 2, newfp);
    printf("fwrite len %d\n", newlen);

    //获取修改后的内容
    fseek(newfp, 0, SEEK_SET);
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, "heheoworld")) {
        printf("readbuf %s\n", readbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fopen 模式"r+"测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       模式"r+":以可读写方式打开文件，该文件必须存在。
  */
int fs_fopen_rplus_test(void)
{
    printf("%s test\n", __func__);
    
    //文件不存在的情况下，打开
    FILE *newfp = fopen(STORAGE_PATH, "r+");
    if(newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //新建文件 创建一个用于读写的空文件
    newfp = fopen(STORAGE_PATH, "w+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "r+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //比较内容
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }

    //修改内容
    newfp = fopen(STORAGE_PATH, "r+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    fseek(newfp, 2, SEEK_SET);
    newlen = fwrite(newbuf, 1, 2, newfp);
    printf("fwrite len %d\n", newlen);

    //获取修改后的内容
    fseek(newfp, 0, SEEK_SET);
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, "heheoworld")) {
        printf("readbuf %s\n", readbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fopen 模式"r"测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       模式"r":以只读方式打开文件，该文件必须存在。
  */
int fs_fopen_r_test(void)
{
    printf("%s test\n", __func__);
    
    //文件不存在的情况下，打开
    FILE *newfp = fopen(STORAGE_PATH, "r");
    if(newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //新建文件 创建一个用于读写的空文件
    newfp = fopen(STORAGE_PATH, "w+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //读取一半的内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 5, SEEK_SET);
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, "world")) {
        printf("readbuf %s\n", readbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //再次读取完整内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //尝试写入内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char writebuf[64] = "testwrite";
    newlen = fwrite(writebuf, 1, strlen(writebuf), newfp);
    printf("fwrite len %d %s\n", newlen, writebuf);
    fclose(newfp);
    
    //再次读取完整内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fopen 模式"wb+"测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       模式"wb+":打开可读写二进制文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
  */
int fs_fopen_wbplus_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于读写的空文件
    FILE *newfp = fopen(STORAGE_PATH, "wb+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //检查读写数据是否一致
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //打开可读写文件，当前文件存在则文件长度清为零
    newfp = fopen(STORAGE_PATH, "wb+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //判断是否为空文件
    fseek(newfp, 0, SEEK_END);
    int len = ftell(newfp);
    if(len != 0) {
        printf("len %d\n", len);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    //定位到开头
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    
    //定位到开头
    fseek(newfp, 0, SEEK_SET);
    
    //不关闭文件直接进行读操作
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //检查读写数据是否一致
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fopen 模式"w+"测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       模式"w+":打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
  */
int fs_fopen_wplus_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于读写的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //检查读写数据是否一致
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //打开可读写文件，当前文件存在则文件长度清为零
    newfp = fopen(STORAGE_PATH, "w+");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //判断是否为空文件
    fseek(newfp, 0, SEEK_END);
    int len = ftell(newfp);
    if(len != 0) {
        printf("len %d\n", len);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    //定位到开头
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    
    //定位到开头
    fseek(newfp, 0, SEEK_SET);
    
    //不关闭文件直接进行读操作
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //检查读写数据是否一致
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fopen 模式"wb"测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       模式"wb":只写打开或新建一个二进制文件；只允许写数据。
  */
int fs_fopen_wb_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "wb");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //比较内容
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //文件名称与已存在的文件相同，则会删除已有文件的内容，文件被视为一个新的空文件
    newfp = fopen(STORAGE_PATH, "wb");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_END);
    int len = ftell(newfp);
    if(len != 0) {
        printf("len %d\n", len);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //写入内容
    newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    
    //读取内容
    fseek(newfp, 0, SEEK_SET);
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    if(newlen != 0) {
        printf("len %d\n", newlen);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    fclose(newfp);
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fopen 模式"w"测试
  *
  * @return     错误码
  * @retval     0       成功
  * @retval     -1      失败
  *
  * @note       模式"w":打开只写文件，若文件存在则文件长度清为0，即该文件内容会消失。若文件不存在则建立该文件。
  */
int fs_fopen_w_test(void)
{
    printf("%s test\n", __func__);
    
    //新建文件 创建一个用于写入的空文件
    FILE *newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);

    //写入内容
    char newbuf[64] = "helloworld";
    int newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    fclose(newfp);

    //读取内容
    newfp = fopen(STORAGE_PATH, "r");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_SET);
    
    char readbuf[64] = {0};
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    fclose(newfp);
    
    //比较内容
    if(strcmp(readbuf, newbuf)) {
        printf("readbuf %s\n", readbuf);
        printf("newbuf  %s\n", newbuf);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //文件名称与已存在的文件相同，则会删除已有文件的内容，文件被视为一个新的空文件
    newfp = fopen(STORAGE_PATH, "w");
    if(!newfp) {
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    fseek(newfp, 0, SEEK_END);
    int len = ftell(newfp);
    if(len != 0) {
        printf("len %d\n", len);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    
    //写入内容
    newlen = fwrite(newbuf, 1, strlen(newbuf), newfp);
    printf("fwrite len %d %s\n", newlen, newbuf);
    
    //读取内容
    fseek(newfp, 0, SEEK_SET);
    
    memset(readbuf, 0, sizeof(readbuf));
    newlen = fread(readbuf, 1, sizeof(readbuf), newfp);
    printf("fread len %d %s\n", newlen, readbuf);
    if(newlen != 0) {
        printf("len %d\n", newlen);
        printf("%s %d failed\n", __func__, __LINE__);
        return -1;
    }
    fclose(newfp);
    
    //测试结束，删除测试文件
    remove(STORAGE_PATH);
    
    printf("%s success\n", __func__);
    
    return 0;
}

/**
  * @brief      fopen 测试
  *
  */
static void fs_fopen_test(void *priv)
{
    fs_fopen_w_test();
    fs_fopen_wb_test();
    fs_fopen_wplus_test();
    fs_fopen_wbplus_test();
    fs_fopen_r_test();
    fs_fopen_rplus_test();
    fs_fopen_rbplus_test();
    fs_fopen_rwplus_test();
    fs_fopen_a_test();
    fs_fopen_aplus_test();
    fs_fopen_abplus_test();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    fs_fopen_test(NULL);
    fs_fseek_test(NULL);
    fs_fwrite_test(NULL);
    fs_fread_test(NULL);
    fs_ftell_test(NULL);
    fs_fgetc_test(NULL);
    fs_fputc_test(NULL);
    fs_fgets_test(NULL);
    fs_fputs_test(NULL);
    
    return 0;
}