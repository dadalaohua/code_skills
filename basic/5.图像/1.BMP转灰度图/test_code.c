#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

//Photo by Ella Olsson from Pexels
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    FILE *fp_src;
    FILE *fp_dst;
    
    char buf[54];
    int src_len;
    int i;
    unsigned char blue, green, red;
    unsigned char gray;

    fp_src = fopen("src.bmp","r");      //打开需要转换的图片
    fp_dst = fopen("dst.bmp", "w+");    //要保存的图片
    
    if(fp_src == NULL || fp_dst == NULL) 
    {
        return -1;
    }
    
    //得到图片大小
    fseek(fp_src, 0, SEEK_END);
    src_len = ftell(fp_src);
    
    //回到开头
    fseek(fp_src, 0, SEEK_SET);
    
    //复制位图信息，前54的字节就是位图信息
    fread(buf, 54, 1, fp_src);
    fwrite(buf, 54, 1, fp_dst);

    //减去位图信息，剩下的长度就是位图数据的长度
    src_len -= 54;
    for(i = 0; i < src_len; i += 3)
    {
        //得到B,G,R三色的数值
        blue  = fgetc(fp_src);
        green = fgetc(fp_src);
        red   = fgetc(fp_src);

        //灰度转换的通用公式
        gray = (red * 0.3 + green * 0.59 + blue * 0.11);
        gray = (red * 0.2126 + green * 0.7152 + blue * 0.0722);
        gray = (red * 0.299 + green * 0.587 + blue * 0.114);
        // gray = (red + green + blue)/3;
        
        //写入数据
        fputc(gray, fp_dst);
        fputc(gray, fp_dst);
        fputc(gray, fp_dst);
    }

    //关闭文件
    fclose(fp_src);
    fclose(fp_dst);
    
    return 0;
}
