#include <stdio.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "queue.h"

#define Q_UART_BUFFER_SIZE  1024

QUEUE_HandleTypeDef qUartTx;
QUEUE_DATA_T BufferUartTx[Q_UART_BUFFER_SIZE];

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    QUEUE_DATA_T data;
    QUEUE_DATA_T buf[] = "world";
    int len = strlen((char *)buf);
    //初始化队列
    Queue_Init(&qUartTx, BufferUartTx, Q_UART_BUFFER_SIZE);
    
    //入队
    Queue_Push(&qUartTx, 'H');
    Queue_Push(&qUartTx, 'e');
    Queue_Push(&qUartTx, 'l');
    Queue_Push(&qUartTx, 'l');
    Queue_Push(&qUartTx, 'o');
    
    //出队
    Queue_Pop(&qUartTx, &data);
    printf("%c\n", data);
    Queue_Pop(&qUartTx, &data);
    printf("%c\n", data);
    Queue_Pop(&qUartTx, &data);
    printf("%c\n", data);
    Queue_Pop(&qUartTx, &data);
    printf("%c\n", data);
    Queue_Pop(&qUartTx, &data);
    printf("%c\n", data);
    
    //多数据入队
    Queue_Push_Array(&qUartTx, buf, len);
    
    memset(buf, 0x00, sizeof(buf));
    
    //多数据出队
    Queue_Pop_Array(&qUartTx, buf, len);
    printf("%s\n", buf);
    
    //入队
    Queue_Push(&qUartTx, 'H');
    
    //查看数据，但数据不出队列
    Queue_Peek(&qUartTx, &data);
    printf("%c\n", data);
    
    //出队
    Queue_Pop(&qUartTx, &data);
    printf("%c\n", data);
    
    //多数据入队
    Queue_Push_Array(&qUartTx, buf, len);
    
    //查看数据，但数据不出队列
    Queue_Peek_Array(&qUartTx, buf, 3);
    printf("%c\n", buf[0]);
    printf("%c\n", buf[1]);
    printf("%c\n", buf[2]);
    
    //多数据出队
    Queue_Pop_Array(&qUartTx, buf, len);
    printf("%s\n", buf);
    
    //获取队列数据量
    printf("cnt: %d\n", Queue_Count(&qUartTx));
    
    //多数据入队
    Queue_Push_Array(&qUartTx, buf, len);
    
    //获取队列数据量
    printf("cnt: %d\n", Queue_Count(&qUartTx));
    
    //清空队列
    Queue_Clear(&qUartTx);
    
    //获取队列数据量
    printf("cnt: %d\n", Queue_Count(&qUartTx));

    return 0;
}