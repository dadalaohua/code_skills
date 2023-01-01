#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "samplerate.h"

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
    
    //默认文件的通道数
    int channel = 2;
    
    //输出文件的默认采样率
    int OutSampleRate = 48000;
    //输出文件的默认通道数
    int Outchannel = 2;
    //输出文件名
    char* Outname = "newpcm.wav";
    
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            Outname = argv[++i];
        } else if (strcmp(argv[i], "-c") == 0) {
            Outchannel = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-s") == 0) {
            OutSampleRate = atoi(argv[++i]);
        } else {
            fprintf(stderr,
                    "Usage: %s OPTIONS\n"
                    "  -o Outname       - 输出文件名, default: '%s'\n"
                    "  -c Outchannel    - 输出文件的通道数, default: '%d'\n"
                    "  -s OutSampleRate - 输出文件的采样率, default: '%d'\n"
                    ,argv[0], Outname, Outchannel, OutSampleRate);
            exit(EXIT_FAILURE);
        }
    }
    
    printf("Outname %s, Outchannel %d, OutSampleRate %d\n", Outname, Outchannel, OutSampleRate);
    
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
    
    //输入文件的通道数
    channel = header.fmt_region.FmtChannels;
    
    //打印头信息
    data_dump(&header);
    
    //新建要转换的wav文件
    void *newwavfp = fopen(Outname, "wb");
    if(newwavfp == NULL) {
        printf("newwavfp NULL\n");
        fclose(wavfp);
        return -1;
    }
    fwrite(&header, 1, sizeof(header), newwavfp);
    
    
    //wav数据段的长度
    int wavlen = header.riff_region.ChunkSize + 8 - headerlen;
    //数据段变为short类型后的长度
    int wavshortlen = wavlen / sizeof(short);
    //打印长度
    printf("wavlen %d wavshortlen %d\n", wavlen, wavshortlen);
    
    //申请用于读取文件的buff
    short* pcmbuffer = malloc(sizeof(short) * wavshortlen);
    
    //申请用于输入和输出的buff，用于采样率转换
    float* in = malloc(sizeof(float) * wavshortlen);
    
    int outlen = (long long)wavshortlen * OutSampleRate / header.fmt_region.SampleRate + 1;
    float* out = malloc(sizeof(float) * outlen);
    
    if(in == NULL || out == NULL) {
        printf("in %p out %p\n", in, out);
        fclose(wavfp);
        fclose(newwavfp);
        
        free(pcmbuffer);
        return -1;
    }
    
    //定义结构体参数
    SRC_DATA src_data;
    src_data.data_in       = in;                                                //输入数据
    src_data.input_frames  = wavshortlen / channel;                             //输入数据的帧数
    src_data.data_out      = out;                                               //输出数据
    src_data.output_frames = outlen / channel;                                  //输出数据的帧数
    src_data.src_ratio     = (float)OutSampleRate/header.fmt_region.SampleRate; //输出采样率/输入采样率
    
    //清空数据缓存区
    memset(in, 0, sizeof(float) * wavshortlen);
    memset(out, 0, sizeof(float) * outlen);
    
    printf("input_frames %ld output_frames %ld\n", src_data.input_frames, src_data.output_frames);
    
    //读取整个音频数据
    if(fread(pcmbuffer, sizeof(short), wavshortlen, wavfp) != 0) {
        //将读取的数据放入输入buff中
        for(int i = 0; i < wavshortlen; i++) {
            in[i] = pcmbuffer[i];
        }
        
        //转换
        int ret = src_simple(&src_data, SRC_LINEAR, channel);   //线性转换器，质量很差，但转换速度非常快
        //int ret = src_simple(&src_data, SRC_ZERO_ORDER_HOLD, channel);    //零阶保持转换器，质量很差，但转换速度非常快
        //int ret = src_simple(&src_data, SRC_SINC_BEST_QUALITY, channel);  //带宽限制插值器，最高品质
        if(ret != 0) {
            printf("src_simple error: %s\n", src_strerror(ret));
            return -1;
        }
        
        //input_frames_used 将设置为用于生成提供的输出帧数的输入帧数
        //output_frames_gen 将设置为生成的输出帧数
        printf("input_frame_used[%ld], out_frame_gen[%ld]\n", src_data.input_frames_used , src_data.output_frames_gen);
        
        
        //输出长度 = 生成的输出帧数 * 通道数 * 每个数据长度
        int output_size = src_data.output_frames_gen * channel * sizeof(short);
        //输出的buff
        short* outbuffer;
        
        //输入与输出的通道数是否相等
        if(channel != Outchannel) {
            if(channel == 2 && Outchannel == 1) {
                //申请用于输出的buff
                outbuffer = malloc(sizeof(short) * src_data.output_frames_gen * channel / 2);
                
                //双声道转单声道
                for(int i = 0, j = 0; i < src_data.output_frames_gen * channel; j++, i += 2) {
                    outbuffer[j] = (out[i] + out[i + 1]) / 2;
                }
                output_size /= 2;
            } else {
                //申请用于输出的buff
                outbuffer = malloc(sizeof(short) * src_data.output_frames_gen * channel * 2);
                
                //单声道转双声道
                for(int i = 0; i < src_data.output_frames_gen * channel; i++) {
                    outbuffer[i * 2]        = out[i];
                    outbuffer[i * 2 + 1]    = out[i];
                }
                output_size *= 2;
            }
        } else {
            //申请用于输出的buff
            outbuffer = malloc(sizeof(short) * src_data.output_frames_gen * channel);
            
            //正常输出
            for(int i = 0; i < src_data.output_frames_gen * channel; i++) {
                outbuffer[i] = out[i];
            }
        }
        
        fwrite(outbuffer, 1, output_size, newwavfp);
        free(outbuffer);
        
        //重新计算wav头数据
        header.riff_region.ChunkSize = output_size + sizeof(header) - 8;
        header.fmt_region.FmtChannels = Outchannel;
        header.fmt_region.SampleRate = OutSampleRate;
        header.fmt_region.ByteRate = header.fmt_region.SampleRate * header.fmt_region.FmtChannels * header.fmt_region.BitsPerSample / 8;
        header.fmt_region.BlockAilgn = header.fmt_region.BitsPerSample * header.fmt_region.FmtChannels / 8;
        
        header.data_region.DataID[0] = 'd';
        header.data_region.DataID[1] = 'a';
        header.data_region.DataID[2] = 't';
        header.data_region.DataID[3] = 'a';
        header.data_region.DataSize = output_size;
        
        //写入wav头
        fseek(newwavfp, 0, SEEK_SET);
        fwrite(&header, 1, sizeof(header), newwavfp);
        
        fflush(newwavfp);
    } else {
        printf("fread failed\n");
    }
    
    fclose(wavfp);
    fclose(newwavfp);
    
    free(pcmbuffer);
    free(in);
    free(out);
    
    //打印输出文件头信息
    data_dump(&header);
    
    return 0;
}
