����7

#include<stdio.h>
int main(void)
{
    int arr[] = {5,4,3,2,1};
    for(int i = -1; i < sizeof(arr)/sizeof(int) - 1; i++)
    {
        printf("%d\n",arr[i+1]);
    }
    printf("end\n");
    return 0;
}
��������

end
ԭ��Ҳ�ܼ򵥣�sizeof(arr)/sizeof(int)�Ľ����unsigend�� 
int���͵�i ��unsigned�Ƚϣ���ת��Ϊһ���ܴ��unsigned��������forѭ�������������㡣