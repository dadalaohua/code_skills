#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//add加

//先fetch再运算，返回的是加以前的值
void sync_fetch_and_add_test(void)
{
    int count = 5;
    printf("\nsync_fetch_and_add test\n");
    printf("before count:%d\n",count);//5
    int retval = __sync_fetch_and_add(&count, 10);

    printf("retval:%d\n",retval);//5
    printf("after count:%d\n",count);//15
}

//先运算再fetch，返回的是加以后的值
void sync_add_and_fetch_test(void)
{
    int count = 5;
    printf("\nsync_add_and_fetch test\n");
    printf("before count:%d\n",count);//5
    int retval = __sync_add_and_fetch(&count, 10);

    printf("retval:%d\n",retval);//15
    printf("after count:%d\n",count);//15
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//sub减

//先fetch再运算，返回的是减以前的值
void sync_fetch_and_sub_test(void)
{
    int count = 20;
    printf("\nsync_fetch_and_sub test\n");
    printf("before count:%d\n",count);//20
    int retval = __sync_fetch_and_sub(&count, 8);

    printf("retval:%d\n",retval);//20
    printf("after count:%d\n",count);//12
}

//先运算再fetch，返回的是减以后的值
void sync_sub_and_fetch_test(void)
{
    int count = 20;
    printf("\nsync_sub_and_fetch test\n");
    printf("before count:%d\n",count);//20
    int retval = __sync_sub_and_fetch(&count, 8);

    printf("retval:%d\n",retval);//12
    printf("after count:%d\n",count);//12
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//or或

//先fetch再运算，返回的是or以前的值
void sync_fetch_and_or_test(void)
{
    unsigned char count = 0xf0;
    printf("\nsync_fetch_and_or test\n");
    printf("before count:0x%x\n",count);//0xf0
    unsigned char retval = __sync_fetch_and_or(&count, 0x55);

    printf("retval:0x%x\n",retval);//0xf0
    printf("after count:0x%x\n",count);//0xf5
}

//先运算再fetch，返回的是or以后的值
void sync_or_and_fetch_test(void)
{
    unsigned char count = 0xf0;
    printf("\nsync_or_and_fetch test\n");
    printf("before count:0x%x\n",count);//0xf0
    unsigned char retval = __sync_or_and_fetch(&count, 0x55);

    printf("retval:0x%x\n",retval);//0xf5
    printf("after count:0x%x\n",count);//0xf5
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//and与

//先fetch再运算，返回的是and以前的值
void sync_fetch_and_and_test(void)
{
    unsigned char count = 0x0f;
    printf("\nsync_fetch_and_and test\n");
    printf("before count:0x%02x\n",count);//0x0f
    unsigned char retval = __sync_fetch_and_and(&count, 0x55);

    printf("retval:0x%02x\n",retval);//0x0f
    printf("after count:0x%02x\n",count);//0x05
}

//先运算再fetch，返回的是and以后的值
void sync_and_and_fetch_test(void)
{
    unsigned char count = 0x0f;
    printf("\nsync_and_and_fetch test\n");
    printf("before count:0x%02x\n",count);//0x0f
    unsigned char retval = __sync_and_and_fetch(&count, 0x55);

    printf("retval:0x%02x\n",retval);//0x05
    printf("after count:0x%02x\n",count);//0x05
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//xor异或

//先fetch再运算，返回的是xor以前的值
void sync_fetch_and_xor_test(void)
{
    unsigned char count = 0x0f;
    printf("\nsync_fetch_and_xor test\n");
    printf("before count:0x%02x\n",count);//0x0f
    unsigned char retval = __sync_fetch_and_xor(&count, 0x55);

    printf("retval:0x%02x\n",retval);//0x0f
    printf("after count:0x%02x\n",count);//0x5a
}

//先运算再fetch，返回的是xor以后的值
void sync_xor_and_fetch_test(void)
{
    unsigned char count = 0x0f;
    printf("\nsync_xor_and_fetch test\n");
    printf("before count:0x%02x\n",count);//0x0f
    unsigned char retval = __sync_xor_and_fetch(&count, 0x55);

    printf("retval:0x%02x\n",retval);//0x5a
    printf("after count:0x%02x\n",count);//0x5a
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//nand与非
/*
    { tmp = *ptr; *ptr = ~(tmp & value); return tmp; }   // nand
    Note: GCC 4.4 and later implement __sync_fetch_and_nand as *ptr = ~(tmp & value) instead of *ptr = ~tmp & value.
    注意: GCC 4.4及更高版本实现了 __sync_fetch_and_nand 作为 * ptr = ~ (tmp & value)而不是 * ptr = ~ tmp & value。
*/

//先fetch再运算，返回的是nand以前的值
void sync_fetch_and_nand_test(void)
{
    unsigned char count = 0x0f;
    printf("\nsync_fetch_and_nand test\n");
    printf("before count:0x%02x\n",count);//0x0f
    unsigned char retval = __sync_fetch_and_nand(&count, 0x55);//*ptr = ~(0x0f & 0x55) = 0xfa

    printf("retval:0x%02x\n",retval);//0x0f
    printf("after count:0x%02x\n",count);//0xfa
}

/*
    { *ptr = ~(*ptr & value); return *ptr; }   // nand
    Note: GCC 4.4 and later implement __sync_nand_and_fetch as *ptr = ~(*ptr & value) instead of *ptr = ~*ptr & value.
    注意: GCC 4.4及更高版本实现了 __sync_nand_and_fetch 为 * ptr = ~ (* ptr & value)而不是 * ptr = ~ * ptr & value。
*/

//先运算再fetch，返回的是nand以后的值
void sync_nand_and_fetch_test(void)
{
    unsigned char count = 0x0f;
    printf("\nsync_nand_and_fetch test\n");
    printf("before count:0x%02x\n",count);//0x0f
    unsigned char retval = __sync_nand_and_fetch(&count, 0x55);//*ptr = ~(0x0f & 0x55) = 0xfa

    printf("retval:0x%02x\n",retval);//0xfa
    printf("after count:0x%02x\n",count);//0xfa
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//compare_and_swap

//bool __sync_bool_compare_and_swap (type *ptr, type oldval, type newval, ...)
//当变量的原值与指定的 oldval 相等时，这两个原语自动将 newval 写给指定变量
//bool 版本的原语在操作成功时返回 1，操作失败时返回 0
void sync_bool_compare_and_swap_test(void)
{
    int count = 5;
    printf("\nsync_bool_compare_and_swap test\n");
    printf("before count:%d\n",count);//5
    
    //如果count == 5，那么数值10被赋值给count，count = 10，并且返回true
    bool retval = __sync_bool_compare_and_swap(&count, 5, 10);

    printf("retval:%d\n",retval);//1
    printf("after count:%d\n",count);//10
    
    //如果count != 8，那么count不变，并且返回false
    retval = __sync_bool_compare_and_swap(&count, 8, 6);

    printf("retval:%d\n",retval);//0
    printf("after count:%d\n",count);//10
}

//type __sync_val_compare_and_swap (type *ptr, type oldval, type newval, ...)
//当变量的原值与指定的 oldval 相等时，这两个原语自动将 newval 写给指定变量
//在操作之前，val 版本返回 * ptr 的内容。
void sync_val_compare_and_swap_test(void)
{
    int count = 5;
    printf("\nsync_val_compare_and_swap test\n");
    printf("before count:%d\n",count);//5
    
    //先返回count的值5，然后如果count == 5，那么数值10被赋值给count，count = 10
    int retval = __sync_val_compare_and_swap(&count, 5, 10);

    printf("retval:%d\n",retval);//5
    printf("after count:%d\n",count);//10
    
    //先返回count的值10，然后如果count == 8，那么数值6被赋值给count，这里不相等，就不会赋值
    retval = __sync_val_compare_and_swap(&count, 8, 6);

    printf("retval:%d\n",retval);//10
    printf("after count:%d\n",count);//10
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//synchronize
//This built-in function issues a full memory barrier. 
//内存屏障
int sync_synchronize_test(void)
{
    __sync_synchronize();
    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//lock_test_and_set
//This built-in function issues a full memory barrier. 
//将value写入*ptr，对*ptr加锁，并返回操作之前*ptr的值。即，try spinlock语义

//lock_release 
// 将0写入到*ptr，并对*ptr解锁。即，unlock spinlock语义

void sync_lock_test_and_set_and_release_test(void)
{
    int count = 5;
    printf("\nsync_lock_test_and_set_and_release test\n");
    printf("before count:%d\n",count);//5
    
    int retval = __sync_lock_test_and_set(&count, 10);
    
    printf("retval:%d\n",retval);//5
    printf("after count:%d\n",count);//10
    
    retval = __sync_lock_test_and_set(&count, 15);
    
    printf("retval:%d\n",retval);//10
    printf("after count:%d\n",count);//15
    
    __sync_lock_release(&count);
    
    printf("after count:%d\n",count);//0
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    //add
    sync_fetch_and_add_test();
    sync_add_and_fetch_test();
    
    //sub
    sync_fetch_and_sub_test();
    sync_sub_and_fetch_test();
    
    //or
    sync_fetch_and_or_test();
    sync_or_and_fetch_test();
    
    //and
    sync_fetch_and_and_test();
    sync_and_and_fetch_test();
    
    //xor
    sync_fetch_and_xor_test();
    sync_xor_and_fetch_test();
    
    //nand
    sync_fetch_and_nand_test();
    sync_nand_and_fetch_test();
    
    //compare_and_swap
    sync_bool_compare_and_swap_test();
    sync_val_compare_and_swap_test();
    
    //synchronize
    sync_synchronize_test();
    
    //lock_test_and_set lock_release
    sync_lock_test_and_set_and_release_test();
    
    return 0;
}