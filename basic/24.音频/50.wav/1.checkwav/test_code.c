/*
https://blog.csdn.net/tyustli/article/details/126240571
 */

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

typedef struct {
    char ChunkID[4];        //'R','I','F','F'
    unsigned int ChunkSize; //从下一个字段首地址开始到文件末尾的总字节数。该字段的数值加 8 为当前文件的实际长度
    char Format[4];         //'W','A','V','E'
} riff_chunk;

typedef struct {
    char FmtID[4];                  //'f','m','t'
    unsigned int FmtSize;           //fmt chunk 的大小，一般有 16/18/20/22/40 字节 (也有超过 40 字节的情况，如果不知道后面部分的含义，直接跳过即可)，超过 16 字节部分为扩展块
    unsigned short FmtTag;          //编码格式代码，其值见 常见编码格式 表，如果上述取值为 16，则此值通常为 1，代表该音频的编码方式是 PCM 编码
    unsigned short FmtChannels;     //声道数目，1 代表单声道，2 代表双声道
    unsigned int SampleRate;        //采样频率，8/11.025/12/16/22.05/24/32/44.1/48/64/88.2/96/176.4/192 kHZ
    unsigned int ByteRate;          //传输速率，每秒的字节数，计算公式为:SampleRate * FmtChannels * BitsPerSample/8
    unsigned short BlockAilgn;      //块对齐，告知播放软件一次性需处理多少字节，公式为： BitsPerSample*FmtChannels/8
    unsigned short BitsPerSample;   //采样位数，一般有8/16/24/32/64，值越大，对声音的还原度越高
} fmt_chunk;

typedef struct {
    char DataID[4];         //'d','a','t','a'
    unsigned int DataSize;  //原始音频数据的大小
} data_chunk;


typedef struct {
    riff_chunk riff_region;
    fmt_chunk fmt_region;
    data_chunk data_region;
} wav_struct;

static void *map_file(const char *path);
static void data_dump(wav_struct *data);

int main(int argc, char *argv[]) {

    assert(sizeof(wav_struct) == 44); /* defensive */

    if (argc < 2) {
        printf("usage: %s file_path\r\n", argv[0]);
        exit(-1);
    }

    /* map file */
    wav_struct *map_data = map_file(argv[1]);

    /* data dump */
    data_dump(map_data);

    /* munmap file */
    munmap(map_data, map_data->riff_region.ChunkSize + 8);

    return 1;
}

static void *map_file(const char *path) {

    assert(path != NULL);

    int fd = open(path, O_RDWR);
    if (fd == -1) {
        goto __release;
    }

#if 0
    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        goto __release;
    }
#endif

    /* get file size */
    struct stat stat;
    int ret = fstat(fd, &stat);
    if (ret == -1) {
        goto __release;
    }

    size_t size = stat.st_size;

    /* map file */
    void *file_data = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(file_data == (void *)-1) {
        goto __release;
    }
    close(fd);

    return file_data;

    /* error handle */
__release:
    perror("map file");
    if (fd > 0) {
        close(fd);
    }
    exit(1);
}

static void data_dump(wav_struct *data) {

    /* RIFF chunk */
    printf("ChunkID                 :");
    for(int i = 0; i < 4; i++) {
        printf("%c", data->riff_region.ChunkID[i]);
    }
    printf("\r\n");
    
    printf("ChunkSize               :%d\r\n", data->riff_region.ChunkSize);
    printf("Format                  :");
    for(int i = 0; i < 4; i++) {
        printf("%c", data->riff_region.Format[i]);
    }
    printf("\r\n");
    printf("\r\n");
    
    /* fmt chunk */
    printf("FmtID                   :");
    for(int i = 0; i < 4; i++) {
        printf("%c", data->fmt_region.FmtID[i]);
    }
    printf("\r\n");
    
    printf("FmtSize                 :%d\r\n", data->fmt_region.FmtSize);
    printf("FmtTag                  :%d (1 PCM 编码)\r\n", data->fmt_region.FmtTag);
    printf("FmtChannels             :%d (1 单声道， 2 双声道)\r\n", data->fmt_region.FmtChannels);
    printf("SampleRate              :%d\r\n", data->fmt_region.SampleRate);
    printf("ByteRate                :%d (计算公式 SampleRate * FmtChannels * BitsPerSample / 8)\r\n", data->fmt_region.ByteRate);
    printf("BlockAilgn              :%d (计算公式 BitsPerSample * FmtChannels / 8)\r\n", data->fmt_region.BlockAilgn);
    printf("BitsPerSample           :%d\r\n", data->fmt_region.BitsPerSample);
    printf("\r\n");
    
    /* data chunk */
    printf("DataID                  :");
    for(int i = 0; i < 4; i++) {
        printf("%c", data->data_region.DataID[i]);
    }
    printf("\r\n");
    printf("DataSize                :%d\r\n", data->data_region.DataSize);
    printf("\r\n");
}
