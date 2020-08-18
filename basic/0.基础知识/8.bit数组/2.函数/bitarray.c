#include <stdlib.h>
#include "bitarray.h"
//常量,将一个字符所占的位数定义为1字节,通常CHAR_BIT=8bit=1byte
const unsigned char A_BYTE = CHAR_BIT;
//掩码
const unsigned char MASK_1 = 1;
//定义真实的bitarray类型
struct bitarray{
    //这就是bitarray真正的核心了,在底层我们使用unsigned char数组来模拟位数组并且用它来存储位信息
    unsigned char* byte_arr;
    //最大位
    unsigned long max_bits;
    //byte_arr数组的长度
    unsigned long len;
} bitarray;

/**接口的实现部分**/

/*
 * 创建一个bit_array
 * name: bitarray_create
 * @param bit 需要创建的位数组宽度,需要注意的是bit的值不能为0且必须为A_BYTE的整数倍,否则会创建失败
 * @return 创建成功返回指向bitarray对象的指针(其实就是bit_array),创建失败返回NULL
 * 
 */
bit_array bitarray_create(unsigned long bits){
    //首先定义一个临时变量
    bit_array tmp=NULL;
    unsigned long  len=0;
    //检查位数bits是否符合要求,不符合要求返回NULL
    if(bits == 0 || (bits%A_BYTE) != 0)
        return NULL;
    //接下来为对象分配空间
    tmp = malloc(sizeof(bitarray));
    //检查有没有分配失败,分配空间失败返回NULL
    if(tmp == NULL)
        return NULL;
    //计算所需的Byte数,也就是byte_arr数组的长度
    len = bits / A_BYTE;
    //为底层的byte_arr分配空间
    tmp->byte_arr = calloc(len,sizeof(unsigned char));
    //检查一下有没有分配成功
    if(tmp->byte_arr == NULL)
    {
        //释放为tmp分配的空间
        free(tmp);
        //返回NULL
        return NULL;
    }
    //
    tmp->len=len;
    tmp->max_bits=bits;
    //返回对象
    return tmp; 
}
/*
 * 销毁已经创建的bit_array对象,释放为它分配的空间
 * name: bitarray_destroy
 * @param target 需要销毁的对象
 * @return 成功返回1,失败返回ERROR_NULL(当target为NULL时)
 * 
 */
int bitarray_destroy(bit_array target){
    if(target == NULL)
        return ERROR_NULL;
    else{
        free(target->byte_arr);//先释放底层数组对象的空间
        free(target);//再释放对象本身
        return 1;
    }
}
 /*
  * 获取目标位数组对象中可容纳的位的数量;注意:位数组的索引是从0开始的,所以max_index=max_bits-1
  * name:  bitarray_max_bits
 * @param target 目标位数组对象
 * @return 成功返回目标位数组的位数量,失败返回0
  */
 unsigned long bitarray_max_bits(bit_array target){
    //检查参数
    if(target == NULL)
        return 0;
    //
    return  target->max_bits;
 }
/*
 * 将目标对象中的某位设置为BIT_STATE_ON,即1
 * name:  bitarray_set_bit
 * @param target 目标位数组对象
 * @param bit 要设置的位
 * @return 成功返回1,失败返回ERROR_BIT(当bit超过bitarray的最大位时)或者ERROR_NULL(当target为NULL时)
 * 
 */
int bitarray_set_bit(bit_array target,unsigned long bit){
    //检查参数
    if(target == NULL)
        return ERROR_NULL;
    if(bit >= target->max_bits)
        return ERROR_BIT;
    //
    unsigned long idx;//bit在底层数组中元素的索引
    unsigned int pos;//bit在其元素的第几位
    //定位元素
    idx = target->len - 1 - (bit/A_BYTE);
    //定位到元素中的位
    pos = (bit % A_BYTE);
    //将指定位设置为开,即BIT_STATE_ON
    target->byte_arr[idx] |= MASK_1<< pos;
    //返回
    return 1;
}
/*
 * 将目标对象中的某位设置为BIT_STATE_OFF,即0
 * name:  bitarray_clear_bit
 * @param target 目标位数组对象
 * @param bit 要设置的位
 * @return 成功返回1,失败返回ERROR_BIT(当bit超过bitarray的最大位时)或者ERROR_NULL(当target为NULL时)
 * 
 */
int bitarray_clear_bit(bit_array target,unsigned long bit){

    //检查参数
    if(target == NULL)
        return ERROR_NULL;
    if(bit >= target->max_bits)
        return ERROR_BIT;
    //
    unsigned long idx;//bit在底层数组中元素的索引
    unsigned int pos;//bit在其元素的第几位
    //定位元素
    idx = target->len - 1 - (bit/A_BYTE);
    //定位到元素中的位
    pos = (bit % A_BYTE);
    //将指定位设置为关,即BIT_STATE_OFF
    target->byte_arr[idx]  &= ~(MASK_1<< pos);
    //返回
    return 1;
}
/*
 * 测试目标对象中的某位的状态
 * name:  bitarray_test_bit
 * @param target 目标位数组对象
 * @param bit 要设置的位
 * @return 成功返回目标位的状态(BIT_STATE_ON或者BIT_STATE_OFF),失败返回ERROR_BIT(当bit超过bitarray的最大位时)或者ERROR_NULL(当target为NULL时)
 * 
 */
 int bitarray_test_bit(bit_array target,unsigned long bit){
    //检查参数
    if(target == NULL)
        return ERROR_NULL;
    if(bit >= target->max_bits)
        return ERROR_BIT;
    //
    unsigned long idx;//bit在底层数组中元素的索引
    unsigned int pos;//bit在其元素的第几位
    //定位元素
    idx = target->len - 1 - (bit/A_BYTE);
    //定位到元素中的位
    pos = (bit % A_BYTE);
    //测试位状态
    if(target->byte_arr[idx] & (MASK_1<< pos) )
        return BIT_STATE_ON;
    else
        return BIT_STATE_OFF;
 }
 