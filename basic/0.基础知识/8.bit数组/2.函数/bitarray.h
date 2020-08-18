#ifndef _BIT_ARRAY_H
#define _BTI_ARRAY_H
//定义错误代码
#define ERROR_BIT -1 
#define ERROR_NULL -2
//定义位的两种状态
#define BIT_STATE_ON 1  //状态:开
#define BIT_STATE_OFF 0  //状态:关
#include <limits.h>
//位数组指针类型,bit_array是指向bitarray类型的指针
typedef struct bitarray*    bit_array;
//
//下面是接口部分

/*
 * 创建一个bit_array
 * name: bitarray_create
 * @param bit 需要创建的位数组宽度,需要注意的是bit的值不能为0且必须为A_BYTE的整数倍,否则会创建失败
 * @return 创建成功返回指向bitarray对象的指针(其实就是bit_array),创建失败返回NULL
 * 
 */
bit_array bitarray_create(unsigned long bits);
/*
 * 销毁已经创建的bit_array对象,释放为它分配的空间
 * name: bitarray_destroy
 * @param target 需要销毁的对象
 * @return 成功返回1,失败返回ERROR_NULL(当target为NULL时)
 * 
 */
int bitarray_destroy(bit_array target);
/*
 * 将目标对象中的某位设置为BIT_STATE_ON,即1
 * name:  bitarray_set_bit
 * @param target 目标位数组对象
 * @param bit 要设置的位
 * @return 成功返回1,失败返回ERROR_BIT(当bit超过bitarray的最大位时)或者ERROR_NULL(当target为NULL时)
 * 
 */
int bitarray_set_bit(bit_array target,unsigned long bit);
/*
 * 将目标对象中的某位设置为BIT_STATE_OFF,即0
 * name:  bitarray_clear_bit
 * @param target 目标位数组对象
 * @param bit 要设置的位
 * @return 成功返回1,失败返回ERROR_BIT(当bit超过bitarray的最大位时)或者ERROR_NULL(当target为NULL时)
 * 
 */
int bitarray_clear_bit(bit_array target,unsigned long bit);
/*
 * 测试目标对象中的某位的状态
 * name:  bitarray_test_bit
 * @param target 目标位数组对象
 * @param bit 要设置的位
 * @return 成功返回目标位的状态(BIT_STATE_ON或者BIT_STATE_OFF),失败返回ERROR_BIT(当bit超过bitarray的最大位时)或者ERROR_NULL(当target为NULL时)
 * 
 */
 int bitarray_test_bit(bit_array target,unsigned long bit);
 /*
  * 获取目标位数组对象中可容纳的位的数量;注意:位数组的索引是从0开始的,所以max_index=max_bits-1
  * name:  bitarray_max_bits
 * @param target 目标位数组对象
 * @return 成功返回目标位数组的位数量,失败返回0
  */
 unsigned long bitarray_max_bits(bit_array target);
#endif