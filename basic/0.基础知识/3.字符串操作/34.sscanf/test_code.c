#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    sscanf函数原型为int sscanf(const char *str, const char *format, ...)。
    将参数str的字符串根据参数format字符串来转换并格式化数据，转换后的结果存于对应的参数内。具体功能如下：

（1）根据格式从字符串中提取数据。如从字符串中取出整数、浮点数和字符串等。

（2）取指定长度的字符串

（3）取到指定字符为止的字符串

（4）取仅包含指定字符集的字符串

（5）取到指定字符集为止的字符串

sscanf可以支持格式字符%[]：

(1)-: 表示范围，如：%[1-9]表示只读取1-9这几个数字 %[a-z]表示只读取a-z小写字母，类似地 %[A-Z]只读取大写字母
(2)^: 表示不取，如：%[^1]表示读取除'1'以外的所有字符 %[^/]表示除/以外的所有字符
(3),: 范围可以用","相连接 如%[1-9,a-z]表示同时取1-9数字和a-z小写字母 
(4)原则：从第一个在指定范围内的数字开始读取，到第一个不在范围内的数字结束
        %s 可以看成%[] 的一个特例 %[^ ](注意^后面有一个空格！)
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    long long id = 0;
    int year = 0;
    int month = 0;
    int day = 0;
    char content[64] = "";
    
    // 返回值 代表了成功分割个数
    int num = sscanf("id:12345678;2022/12/15,Hello", "id:%lld;%d/%d/%d,%s", &id, &year, &month, &day, content);
    printf("id = %lld, year = %d, month = %d, day = %d\n", id, year, month, day);   //id = 12345678, year = 2022, month = 12, day = 15
    printf("content : %s\n", content);  //content : Hello
    printf("成功转换个数：%d\n\n", num);
    
    year = month = day = 0;
    num = sscanf("20240630", "%04d%02d%02d", &year, &month, &day);  //"%04d%02d%02d"是用来解析字符串的格式，%表示格式转换的开始，d表示转换为一个整数，04作为d的修饰，表示这是一个长度为4位的整数，不足4位时以0补齐
    printf("year = %d, month = %d, day = %d\n", year, month, day);  //year = 2024, month = 6, day = 30
    printf("成功转换个数：%d\n\n", num);
    
    year = month = day = 0;
    num = sscanf("20240630", "%d%d%d", &year, &month, &day);    //这样只能成功转换一个，其余值为默认值
    printf("year = %d, month = %d, day = %d\n", year, month, day);  //year = 20240630, month = 0, day = 0
    printf("成功转换个数：%d\n\n", num);
    
    year = month = day = 0;
    num = sscanf("2024 06 30", "%d%d%d", &year, &month, &day);  //遇见空格结束，可以成功转换三个
    printf("year = %d, month = %d, day = %d\n", year, month, day);  //year = 2024, month = 6, day = 30
    printf("成功转换个数：%d\n\n", num);
    
    char str[] = "12345abcde";
    char buf[1024] = {0};
    num = sscanf(str, "%*d%s", buf); //%*d 表示忽略整数
    printf("buf : %s\n",buf);   //buf : abcde
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf(str, "%6s", buf);//buf长度限制为6，只会读取6个字符
    printf("buf : %s\n",buf);   //buf : 12345a
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf(str, "%[0-9]", buf);//读取0-9数字
    printf("buf : %s\n",buf);   //buf : 12345
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf("12345abcdeABC", "%[0-9, a-z]", buf);//读取0-9数字和a-z小写字母
    printf("buf : %s\n",buf);   //buf : 12345abcde
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf("12345abc1deA2BCa", "%[0-9, a-z, A-Z]", buf);//读取0-9数字和a-z小写字母和A-Z大写字母
    printf("buf : %s\n",buf);   //buf : 12345abc1deA2BCa
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf("12345abcdeABC", "%[0-9a-z]", buf);//读取0-9数字和a-z小写字母，中间没有逗号
    printf("buf : %s\n",buf);   //buf : 12345abcde
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf("12345abcdeABC", "%3[0-9]", buf);//buf长度限制为3，只会读取3个0-9数字
    printf("buf : %s\n",buf);   //buf : 123
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf("12345abc3d6eA2BCa", "%*[0-9]%s", buf);//忽略0-9数字，直到非数字
    printf("buf : %s\n",buf);   //buf : abc3d6eA2BCa
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf("12345abc3d6eA2BCa", "%*d%[a-z]", buf); //忽略0-9数字，读取a-z小写字母，直到非a-z小写字母为止
    printf("buf : %s\n",buf);   //buf : abc
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf("dcbaefg6eA2BCa", "%[abcd]", buf); //读取abcd小写字母
    printf("buf : %s\n",buf);   //buf : dcba
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf("dc1Abaefg6eA2BCa", "%[^f]", buf); //读取除f以外的其他字符
    printf("buf : %s\n",buf);   //buf : dc1Abae
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf("dc1Abaefg6eA2BCa", "%[^g-z]", buf); //读取除g-z以外的其他字符
    printf("buf : %s\n",buf);   //buf : dc1Abaef
    printf("成功转换个数：%d\n\n", num);
    
    num = sscanf("123abcde#hello@123abc45", "%*[^#]#%[^@]", buf); //忽略除#以外的其他字符，然后取#之后除@以外的其他字符，也就是截取中间的字符
    printf("buf : %s\n",buf);   //buf : hello
    printf("成功转换个数：%d\n\n", num);
    
    double fpnum1, fpnum2;
    num = sscanf("12345.123456789 12345.123456789", "%lf %lf", &fpnum1, &fpnum2); //读取浮点数
    printf("fpnum1 = %.9lf, fpnum2 = %lf\n", fpnum1, fpnum2);   //fpnum1 = 12345.123456789, fpnum2 = 12345.123457
    printf("成功转换个数：%d\n\n", num);
    
    const char *s = "https://github.com:5678";
    char protocol[32] = {0};
    char host[128] = {0};
    char port[8] = {0};
    sscanf(s,"%[^:]://%[^:]:%[1-9]",protocol,host,port);
    
    printf("protocol: %s\n",protocol);
    printf("host: %s\n",host);
    printf("port: %s\n",port);
    
    return 0;
}