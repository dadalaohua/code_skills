返回数字的高32位或低32位

内核中可以查看
include/linux/kernel.h

kernel 5.8

/**
 * upper_32_bits - return bits 32-63 of a number
 * @n: the number we're accessing
 *
 * A basic shift-right of a 64- or 32-bit quantity.  Use this to suppress
 * the "right shift count >= width of type" warning when that quantity is
 * 32-bits.
 */
#define upper_32_bits(n) ((u32)(((n) >> 16) >> 16))

分两次右移16bit，可以解决放入32bit数会有编译 警告： 右移次数大于或等于类型宽度