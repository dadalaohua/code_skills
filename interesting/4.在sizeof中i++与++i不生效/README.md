����2

#include<stdio.h>
int main(void)
{
    int i = 10;
    printf("%zu\n",sizeof(i++));
    printf("%zu\n",sizeof(++i));
    printf("%d\n",i);
    return 0;
}
��������

4
4
10
sizeofʵ�����õĶ��������͡�sizeof�еı��ʽ�������ᱻִ�С�