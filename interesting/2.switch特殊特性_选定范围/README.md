����0��

#include<stdio.h>
int main(void)
{
    int c = 5;
    switch(c)
    {
        case 0 ... 10:
            printf("0-->10\n");
            break;
        case 11 ... 20:
            printf("11-->20\n");
            break;
        default:
            printf("other\n");
    }
    return 0;
}
��������

0-->10
�������Ա�����������֧�֣����Ǳ�׼�в�δ�ᵽ��