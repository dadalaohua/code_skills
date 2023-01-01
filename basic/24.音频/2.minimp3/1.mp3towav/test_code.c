#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMP3_IMPLEMENTATION
#include "minimp3.h"

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

static char *wav_header(int hz, int ch, int bips, int data_bytes)
{
    static char hdr[44] = "RIFFsizeWAVEfmt \x10\0\0\0\1\0ch_hz_abpsbabsdatasize";
    unsigned long nAvgBytesPerSec = bips*ch*hz >> 3;
    unsigned int nBlockAlign      = bips*ch >> 3;

    *(int32_t *)(void*)(hdr + 0x04) = 44 + data_bytes - 8;   /* File size - 8 */
    *(int16_t *)(void*)(hdr + 0x14) = 1;                     /* Integer PCM format */
    *(int16_t *)(void*)(hdr + 0x16) = ch;
    *(int32_t *)(void*)(hdr + 0x18) = hz;
    *(int32_t *)(void*)(hdr + 0x1C) = nAvgBytesPerSec;
    *(int16_t *)(void*)(hdr + 0x20) = nBlockAlign;
    *(int16_t *)(void*)(hdr + 0x22) = bips;
    *(int32_t *)(void*)(hdr + 0x28) = data_bytes;
    return hdr;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s file_path\r\n", argv[0]);
        exit(-1);
    }

    //输出文件名
    char* Outname = "newpcm.wav";
    
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            Outname = argv[++i];
        } else {
            fprintf(stderr,
                    "Usage: %s OPTIONS\n"
                    "  -o Outname       - 输出文件名, default: '%s'\n"
                    ,argv[0], Outname);
            exit(EXIT_FAILURE);
        }
    }
    
    unsigned char *input_buf = NULL;
    int data_size = 0;
    //打开MP3文件
    FILE* file = fopen(argv[1], "r");

    //获取MP3文件长度
    fseek(file, 0, SEEK_END);
    data_size = (int)ftell(file);

    //读取整个MP3文件
    fseek(file, 0, SEEK_SET);
    input_buf = malloc(data_size);
    fread(input_buf, 1, data_size, file);
    fclose(file);

    //初始化minimp3的解码器结构
    static mp3dec_t mp3d;
    mp3dec_init(&mp3d);

    //定义mp3dec_frame_info_t
    mp3dec_frame_info_t info;
    short pcm[MINIMP3_MAX_SAMPLES_PER_FRAME];
    int mp3len = 0;
    
    //新建要转换的wav文件
    void *newwavfp = fopen(Outname, "wb");
    if(newwavfp == NULL) {
        printf("newwavfp NULL\n");
        return -1;
    }
    
    //偏移wav头的位置
    fseek(newwavfp, 44, SEEK_SET);
    
    int output_size = 0;
    //逐帧解码
    int samples = mp3dec_decode_frame(&mp3d, input_buf, data_size, pcm, &info);
    //文件的通道数
    int Outchannel = info.channels;
    //文件的采样率
    int OutSampleRate = info.hz;
    while(samples) {
        fwrite(pcm, 1, samples * sizeof(short) * Outchannel, newwavfp);
        output_size += samples * sizeof(short) * Outchannel;
        mp3len += info.frame_bytes;
        samples = mp3dec_decode_frame(&mp3d, input_buf + mp3len, data_size - mp3len, pcm, &info);
    }
    
    //创建wav头
    wav_struct header;
    
    //填写wav头数据
    // header.riff_region.ChunkID[0] = 'R';
    // header.riff_region.ChunkID[1] = 'I';
    // header.riff_region.ChunkID[2] = 'F';
    // header.riff_region.ChunkID[3] = 'F';
    // header.riff_region.ChunkSize = output_size + sizeof(header) - 8;
    // header.riff_region.Format[0] = 'W';
    // header.riff_region.Format[1] = 'A';
    // header.riff_region.Format[2] = 'V';
    // header.riff_region.Format[3] = 'E';
    
    // header.fmt_region.FmtID[0] = 'f';
    // header.fmt_region.FmtID[1] = 'm';
    // header.fmt_region.FmtID[2] = 't';
    // header.fmt_region.FmtID[3] = ' ';
    // header.fmt_region.FmtSize = 16;
    // header.fmt_region.FmtTag = 1;
    // header.fmt_region.FmtChannels = Outchannel;
    // header.fmt_region.SampleRate = OutSampleRate;
    // header.fmt_region.BitsPerSample = 16;
    // header.fmt_region.ByteRate = header.fmt_region.SampleRate * header.fmt_region.FmtChannels * header.fmt_region.BitsPerSample / 8;
    // header.fmt_region.BlockAilgn = header.fmt_region.BitsPerSample * header.fmt_region.FmtChannels / 8;
    
    // header.data_region.DataID[0] = 'd';
    // header.data_region.DataID[1] = 'a';
    // header.data_region.DataID[2] = 't';
    // header.data_region.DataID[3] = 'a';
    // header.data_region.DataSize = output_size;
    
    memcpy(&header, wav_header(OutSampleRate, Outchannel, 16, output_size), sizeof(header));
    
    
    //写入wav头
    fseek(newwavfp, 0, SEEK_SET);
    fwrite(&header, 1, sizeof(header), newwavfp);
    fflush(newwavfp);
    fclose(newwavfp);
    
    free(input_buf);
    
    //打印输出文件头信息
    data_dump(&header);
    
    return 0;
}
