#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sonic.h"

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
    char ListID[4];         //'L','I','S','T'
    unsigned int ListSize;  //ListData的大小
} list_chunk;

typedef struct {
    riff_chunk riff_region;
    fmt_chunk fmt_region;
    data_chunk data_region;
} wav_struct;

typedef struct {
    riff_chunk riff_region;
    fmt_chunk fmt_region;
    list_chunk list_region;
    data_chunk data_region;
} wav_struct_2;

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

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s file_path\r\n", argv[0]);
        exit(-1);
    }
    
    //默认认为wav头长度为44
    int headerlen = 44;
    
    //输出文件名
    char* Outname = "newpcm.wav";
    float OutSpeed = 1.0;
    float OutPitch = 1.0;
    float OutRate = 1.0;
    float OutVolume = 1.0;
    
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            Outname = argv[++i];
        } else if (strcmp(argv[i], "-s") == 0) {
            OutSpeed = atof(argv[++i]);
        } else if (strcmp(argv[i], "-p") == 0) {
            OutPitch = atof(argv[++i]);
        } else if (strcmp(argv[i], "-r") == 0) {
            OutRate = atof(argv[++i]);
        } else if (strcmp(argv[i], "-v") == 0) {
            OutVolume = atof(argv[++i]);
        } else {
            fprintf(stderr,
                    "Usage: %s OPTIONS\n"
                    "  -o Outname       - 输出文件名, default: '%s'\n"
                    "  -s OutSpeed      - 速度（变速不变调）, default: '%0.1f'\n"
                    "  -p OutPitch      - 音调（变调不变速）, default: '%0.1f'\n"
                    "  -r OutRate       - 速率（变速变调）, default: '%0.1f'\n"
                    "  -v OutVolume     - 音量, default: '%0.1f'\n"
                    ,argv[0], Outname, OutSpeed, OutPitch, OutRate, OutVolume);
            exit(EXIT_FAILURE);
        }
    }
    
    //读取wav头
    wav_struct header;
    void *wavfp = fopen(argv[1], "rb");
    if(wavfp == NULL) {
        printf("wavfp NULL\n");
        return -1;
    }
    fread(&header, 1, sizeof(header), wavfp);
    
    //如果不为data，而是LIST，则获取ListSize，然后跳过该区域
    if(header.data_region.DataID[0] != 'd') {
        if(header.data_region.DataID[0] == 'L' &&
            header.data_region.DataID[1] == 'I' &&
            header.data_region.DataID[2] == 'S' &&
            header.data_region.DataID[3] == 'T') {
            
            list_chunk tmp_chunk;
            memcpy(&tmp_chunk, &header.data_region, sizeof(list_chunk));
            
            fseek(wavfp, sizeof(header) + tmp_chunk.ListSize, SEEK_SET);
            fread(&header.data_region, 1, sizeof(data_chunk), wavfp);
            
            headerlen += tmp_chunk.ListSize + 8;
        }
    }
    
    //文件的通道数
    int OutChannel = header.fmt_region.FmtChannels;
    //文件的采样率
    int OutSampleRate = header.fmt_region.SampleRate;
    
    printf("OutChannel %d OutSampleRate %d\n", OutChannel, OutSampleRate);
    
    //打印头信息
    data_dump(&header);
    
    //新建要转换的wav文件
    void *newwavfp = fopen(Outname, "wb");
    if(newwavfp == NULL) {
        printf("newwavfp NULL\n");
        fclose(wavfp);
        return -1;
    }
    //偏移wav头
    fseek(newwavfp, sizeof(header), SEEK_SET);
    
#define IN_LIMIT_LEN 4096
    
    //申请用于读取文件的buff
    short* pcmbuffer = malloc(sizeof(short) * IN_LIMIT_LEN);
    //创建一个 sonic 流
    sonicStream tempoStream = sonicCreateStream(OutSampleRate, OutChannel);
    if(tempoStream) {
        sonicSetSpeed(tempoStream, OutSpeed);   //速度（变速不变调）
        sonicSetPitch(tempoStream, OutPitch);   //音调（变调不变速）
        sonicSetRate(tempoStream, OutRate);     //速率（变速变调）
        sonicSetVolume(tempoStream, OutVolume); //音量
    } else {
        printf("tempoStream == NULL\n");
        return -1;
    }
    
    //统计输出的音频总长度
    int output_sumsize = 0;
    //读取整个音频数据
    int samplesRead;
    do {
        //读取数据
        samplesRead = fread(pcmbuffer, sizeof(short), IN_LIMIT_LEN, wavfp);
        if(samplesRead == 0) {
            sonicFlushStream(tempoStream);
        } else {
            //将数据写入流中以加速或降低速度
            int ret = sonicWriteShortToStream(tempoStream, pcmbuffer, samplesRead / OutChannel);
            if(ret == 0) {
                return -1;
            }
        }
        
        int samplesWritten;
        do {
            //从流中读取数据
            samplesWritten = sonicReadShortFromStream(tempoStream, pcmbuffer, IN_LIMIT_LEN / OutChannel);
            if(samplesWritten == 0)
                break;
            
            //写入文件
            fwrite(pcmbuffer, sizeof(short), samplesWritten * OutChannel, newwavfp);
            //统计输出的音频长度
            output_sumsize += (samplesWritten * OutChannel * sizeof(short));
        } while(samplesWritten > 0);
    } while (samplesRead > 0);
    
    //重新计算wav头数据
    header.riff_region.ChunkSize = output_sumsize + sizeof(header) - 8;
    header.fmt_region.FmtChannels = OutChannel;
    header.fmt_region.SampleRate = OutSampleRate;
    header.fmt_region.ByteRate = header.fmt_region.SampleRate * header.fmt_region.FmtChannels * header.fmt_region.BitsPerSample / 8;
    header.fmt_region.BlockAilgn = header.fmt_region.BitsPerSample * header.fmt_region.FmtChannels / 8;
    
    header.data_region.DataID[0] = 'd';
    header.data_region.DataID[1] = 'a';
    header.data_region.DataID[2] = 't';
    header.data_region.DataID[3] = 'a';
    header.data_region.DataSize = output_sumsize;
    
    //写入wav头
    fseek(newwavfp, 0, SEEK_SET);
    fwrite(&header, 1, sizeof(header), newwavfp);
    
    //清理释放内存
    sonicDestroyStream(tempoStream);
    
    fflush(newwavfp);
    
    fclose(wavfp);
    fclose(newwavfp);
    
    free(pcmbuffer);
    
    //打印输出文件头信息
    data_dump(&header);
    
    return 0;
}
