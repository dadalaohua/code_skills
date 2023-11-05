#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    FILE *fp_src;
    FILE *fp_dst;
    
    int src_len;
    int i;
    unsigned char blue, green, red;
    unsigned char val[2];

    fp_src = fopen("src.bmp","r");      //打开需要转换的图片
    fp_dst = fopen("dst.bin", "w+");    //要保存的图片
    
    if(fp_src == NULL || fp_dst == NULL) {
        return -1;
    }
    
    //得到图片大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 54, SEEK_SET);

    //减去位图信息，剩下的长度就是位图数据的长度
    src_len -= 54;
    
    int output_len = src_len / 3;
    for(i = 0; i < output_len; i ++) {
        //得到B,G,R三色的数值
        blue  = fgetc(fp_src);
        green = fgetc(fp_src);
        red   = fgetc(fp_src);
        
        val[0] = ((green & 0xFC) << 3) | ((blue & 0xF8) >> 3);
        val[1] = (red & 0xF8) | ((green & 0xFC) >> 5);
        
        //写入数据
        fputc(val[0], fp_dst);
        fputc(val[1], fp_dst);
    }
    
    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}