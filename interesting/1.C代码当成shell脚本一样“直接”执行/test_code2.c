#if 0
proName="${0%.*}";  #去掉文件名后缀，作为程序名
gcc -o $proName "$0";
./$proName "$@";   #传入命令行参数
rm $proName;
exit;
#endif

#include<stdio.h>

int main(int argc, char* argv[])
{ 
    printf("test code 2\n");
    
    return 0;
}
