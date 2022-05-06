#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <sys/resource.h>

// 用来存储栈区的起始地址
size_t top_stack;
/************************************************************************/
/*                                                                      */
/************************************************************************/
void print_stack1()
{
    size_t used, avail;
    pthread_attr_t attr;
    void *stack_addr;
    size_t stack_size;

    // 获取栈寄存器 ESP 的当前值
    size_t esp_val;
    asm("movl %%esp, %0" : "=m"(esp_val) :);

    // 通过线程属性，获取栈区的起始地址和空间总大小
    memset(&attr, 0, sizeof(pthread_attr_t));
    pthread_getattr_np(pthread_self(), &attr);
    pthread_attr_getstack(&attr, &stack_addr, &stack_size);
    pthread_attr_destroy(&attr);

    printf("espVal = %x \n", esp_val);
    printf("statck top   = %p \n", stack_addr);
    printf("stack bottom = %p \n", stack_addr + stack_size);

    avail = esp_val - (size_t)stack_addr;
    used = stack_size - avail;

    printf("print_stack1: used = %d, avail = %d, total = %d \n", 
            used, avail, stack_size);
}

void print_stack2()
{
    size_t used, avail;
    
    size_t esp_val;
    asm("movl %%esp, %0" : "=m"(esp_val) :);
    printf("esp_val = %x \n", esp_val);

    used = top_stack - esp_val;
    
    struct rlimit limit;
    getrlimit(RLIMIT_STACK, &limit);
    avail = limit.rlim_cur - used;
    printf("print_stack2: used = %d, avail = %d, total = %d \n", 
            used, avail, used + avail);
}

void print_stack3()
{
    int x = 0;
    size_t used, avail;
    // 局部变量的地址，可以近似认为是 ESP 寄存器的值
    size_t tmp = (size_t)&x;
    used =  top_stack - tmp;

    struct rlimit limit;
    getrlimit(RLIMIT_STACK, &limit);
    avail = limit.rlim_cur - used;
    printf("print_stack3: used = %d, avail = %d, total = %d \n", 
            used, avail, used + avail);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
/*     //方式一
    print_stack1(); */
    
/*     //方式二
    int x = 0;
    // 记录栈区的起始地址(近似值)
    top_stack = (size_t)&x; 
    print_stack2(); */
    
    //方式三
    int x = 0;
    // 记录栈区的起始地址(近似值)
    top_stack = (size_t)&x;
    print_stack3();
    
    return 0;
}