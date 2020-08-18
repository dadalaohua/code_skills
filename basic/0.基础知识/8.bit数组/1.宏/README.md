位数组(bit数组) 
使用到位数组的代码，一般出于两个考虑： 1. 降低存储空间。2. 加快查找效率(能迅速判断某个地元素是否在一个集合中)。
知识准备
1. 计算机中的位操作: 与(&)、或(|) 、非(~)
　　1 & 1 = 1　　　　　　　　1 | 1 = 1　　　　　　　　~1 = 0
　　1 & 0 = 0　　　　　　　　1 | 0 = 1　　　　　　　　~0 = 1　　　　　　　　　　　　　　　　　　
　　0 & 1 = 0　　　　　　　　0 | 1 = 1
　　0 & 0 = 0　　　　　　　　0 | 0 = 0
2.  左移(<<)和右移(>>)
　　左移一位相当于乘以2。左移操作后，右边空缺位自动补0。右移(本文仅考虑逻辑右移)与左移相反方向操作，相当于除以2，左边空缺自动补0。
3. 置1、置0，判断置位。
  eg: x = 221,其二进制为11011101，若要将它的第5位由0变为1(置1)，则只须第5位与1或即可
    11011101
    00100000
   |--------
    11111101
若要将它的第4位由1变为0(置0)，则只须第4位与0与即可
    11011101
    11101111
   &--------
    11001101
判断第5位是否置1
    11111101
    00100000
   &--------
    00100000  (相与的结果非0则表明相应位已置1，否则置0)
4.  非(~)运算
　　eg: x = 221,其二进制为11011101
    11011101
   ~--------
    00100010
实例演示
假设要求11个数(0~10)存储在位数组里，11个数就需要11个bit位， 而1个byte有8个bit位，故须2个byte才能存储11个数。0存储在第0个byte的第0位，1存储在第0个byte的第1位...存储在第1个byte的第0位，9存储在第1个byte的第1位，10存储在第1个byte的第2位。如下
    |high                      low|
    |--- 1 byte ---|--- 0 byte ---|
    0 0 0 0 0 0 0 0|0 0 0 0 0 0 0 0
             10 9 8 7 6 5 4 3 2 1 0
一个数x(非负整数)若要存储在位数组里， 会面临两个问题：
1. x存储在第几个byte里？
　　因为一个byte可以存储8个bit，那很显然，x应该存储在第(x/8)个byte里。
2. x存储在第(x/8)个byte的第几位上？
　　通过观察，x应该存储在第(x%8)位上。
综上， x应该存储在第(x/8)个byte的第(x%8)位上。
在计算机里，位操作比除法和求模操作更高效点。x/8 相当于 x>>3(右移一位，相当于除以2；右移三位，相当于除以8)；x%8相当于x&0x7。
我们要使得x存储在位数组里，就是要使得第(x>>3)个byte的第(x&0x7)位上置1。由知识准备第3点的置1，可以得出，要使第0位置1，则与之相与的数为1(00000001)；要使第1位置1，则与之相与的数为2(00000010)；要使第2位置1，则与之相与的数为4(00000100) ...
由上可得，把x存储在位数组里，则需要：
　　bitArray[x>>3] |= (1<<(x&0x7))
进而可以得出，判断x存储在位数组里，则需要返回
       bitArray[x>>3] & (1<<(x&0x7))
把x从位数组里删除，则需要
　　bitArray[x>>3] &= ~(1<<(x&0x7))
C语言实现举例

#include <stdlib.h>
#include <stdio.h>
 
#define SHIFT 3  
#define MASK 0x7 
 
#define BITARRAY_SIZE(size)             ((size >> SHIFT) + 1)
#define BYTE_INDEX(num)                 (num >> SHIFT)
#define ADD_TO_BITARRAY(array, num)     (array[BYTE_INDEX(num)] |= (1 << (num & MASK)))
#define IS_IN_BITARRAY(array, num)      (array[BYTE_INDEX(num)] & (1 << (num & MASK)))
#define CLEAR_BITARRAY(array, num)      (array[BYTE_INDEX(num)] &= ~(1 << (num & MASK)))
 
//检测
void test(int value)
{
    if (value)
    {
        printf("In the array.\n");
    }
    else
    {
        printf("Not in the array.\n");
    }
}
 
int main()
{
    //存储0~10这11个数
    int max_size = 11;
    //存储9
    int number = 9;
    char *bitArray = (char*)malloc(BITARRAY_SIZE(max_size) * sizeof(char));
     
    printf("Init: ");
    test(IS_IN_BITARRAY(bitArray, number));
 
    //9放到位数组上
    ADD_TO_BITARRAY(bitArray, number);
    printf("ADD_TO_BITARRAY: ");
    test(IS_IN_BITARRAY(bitArray, number));
     
    //9从位数组上清除
    CLEAR_BITARRAY(bitArray, number);
    printf("CLEAR_BITARRAY: ");
    test(IS_IN_BITARRAY(bitArray, number));
     
    if (bitArray)
    {
        free(bitArray);
        bitArray = NULL;
    }
    return 0;
}
 
其它比较高级的语言，封装成特定的类去实现位数组，提供了丰富的操作位的方法，比较方便。如：
C++
bitset
C#
BitArray
JAVA
BitSet
GO
无