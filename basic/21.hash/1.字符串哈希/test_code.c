#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
 *  @brief  BKDR Hash Function  
 *  @detail 本算法由于在Brian Kernighan与Dennis Ritchie的《The C Programming Language》一书被展示而得名，
 *          是一种简单快捷的hash算法，也是Java目前采用的字符串的Hash算法（累乘因子为31）。
 */
size_t BKDRHash(char *str)
{
    size_t hash = 0;

    while (*str) {
        hash = hash * 131 + (*str++);   //也可以乘以31、131、1313、13131、131313 etc..
        //hash = hash << 7 + hash << 1 + hash + (*str++); //也可以将乘法分解为位运算及加减法
    }

     return hash;
}

/*
 *  @brief  SDBM Hash Function  
 *  @detail 本算法是由于在开源项目SDBM（一种简单的数据库引擎）中被应用而得名，
 *          它与BKDRHash思想一致，只是种子不同而已。
 */
size_t SDBMHash(char *str)
{
    size_t hash = 0;

    while (*str) {
        hash = 65599 * hash + (*str++);
        //hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

/*
 *  @brief  RS Hash Function
 *  @detail 因Robert Sedgwicks在其《Algorithms in C》一书中展示而得名
 *  
 */
size_t RSHash(char *str)
{
    size_t hash = 0;
    size_t magic = 63689;

    while (*str){
        hash = hash * magic + (*str++);
        magic *= 378551;
    }

    return hash;
}

/*
 *  @brief  AP Hash Function
 *  @detail 由Arash Partow发明的一种hash算法
 *  
 */
size_t APHash(char *str)
{
    size_t hash = 0;
    int i;

    for (i = 0; *str; i++) {
        if ((i & 1) == 0) {
            hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
        } else {
            hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
        }
    }

    return hash;
}

/*
 *  @brief  JS Hash Function
 *  @detail 由Justin Sobel发明的一种hash算法。
 */
size_t JSHash(char *str)
{
    size_t hash = 1315423911;

    while (*str) {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }

    return hash;
}

/*
 *  @brief  DEK Function
 *  @detail 本算法是由于Donald E. Knuth在《Art Of Computer Programming Volume 3》中展示而得名。
 */
size_t DEKHash(char *str)
{
    size_t hash = 1315423911;

    while (*str) {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str++);
    }

    return hash;
}

/*
 *  @brief  FNV Hash Function
 *  @detail Unix system系统中使用的一种著名hash算法，后来微软也在其hash_map中实现。
 */
size_t FNVHash(char *str)
{
    size_t hash = 2166136261;

    while (*str) {
        hash *= 16777619;
        hash ^= (*str++);
    }

    return hash;
}

/*
 *  @brief  DJB Hash Function
 *  @detail 由Daniel J. Bernstein教授发明的一种hash算法。
 */
size_t DJBHash(char *str)
{
    size_t hash = 5381;

    while (*str) {
        hash += (hash << 5) + (*str++);
    }

    return hash;
}

/*
 *  @brief  DJB Hash Function 2
 *  @detail 由Daniel J. Bernstein 发明的另一种hash算法。
 */
size_t DJB2Hash(char *str)
{
    size_t hash = 5381;

    while (*str) {
        hash = hash * 33 ^ (*str++);
    }

    return hash;
}

/*
http://www.cse.yorku.ca/~oz/hash.html
this algorithm (k=33) was first reported by dan bernstein many years ago in comp.lang.c. another version 
of this algorithm (now favored by bernstein) uses xor: hash(i) = hash(i - 1) * 33 ^ str[i]; 
the magic of number 33 (why it works better than many other constants, prime or not) has never been adequately explained.
*/
/*和上面的DJBHash一模一样*/
// unsigned long DJB2Hash_2(unsigned char *str)
// {
    // unsigned long hash = 5381;
    // int c;

    // while (c = *str++)
        // hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    // return hash;
// }

/*
 *  @brief  PJW Hash Function
 *  @detail 本算法是基于AT&T贝尔实验室的Peter J. Weinberger的论文而发明的一种hash算法。
 */
size_t PJWHash(char *str)
{
    size_t TotalBits        = sizeof(size_t) * 8;
    size_t ThreeQuarters    = (TotalBits * 3) / 4;
    size_t OneEighth        = TotalBits / 8;
    size_t HighBits         = ((size_t)-1) << (TotalBits - OneEighth);
    
    size_t hash  = 0;
    size_t magic = 0;

    while (*str) {
        hash = (hash << OneEighth) + (*str++);
        if ((magic = hash & HighBits) != 0) {
            hash = ((hash ^ (magic >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}

/*
 *  @brief  ELF Hash Function
 *  @detail 由于在Unix的Extended Library Function被附带而得名的一种hash算法，它其实就是PJW Hash的变形
 */
size_t ELFHash(char *str)
{
    size_t TotalBits        = sizeof(size_t) * 8;
    size_t ThreeQuarters    = (TotalBits * 3) / 4;
    size_t OneEighth        = TotalBits / 8;
    size_t HighBits         = ((size_t)-1) << (TotalBits - OneEighth);
    
    size_t hash  = 0;
    size_t magic = 0;

    while (*str) {
        hash = (hash << OneEighth) + (*str++);
        if ((magic = hash & HighBits) != 0) {
            hash ^= (magic >> ThreeQuarters);  
            hash &= ~magic;
        }
    }

    return hash;
}

/*
http://www.cse.yorku.ca/~oz/hash.html
lose lose
This hash function appeared in K&R (1st ed) but at least the reader was 
warned: "This is not the best possible algorithm, but it has the merit 
of extreme simplicity." This is an understatement; It is a terrible 
hashing algorithm, and it could have been much better without sacrificing 
its "extreme simplicity." [see the second edition!] Many C programmers  use 
this function without actually testing it, or checking something like Knuth's 
Sorting and Searching, so it stuck. It is now found mixed with otherwise 
respectable code, eg. cnews. sigh.
*/
/* unsigned long lose_lose_hash(unsigned char *str)
{
    unsigned int hash = 0;
    int c;

    while (c = *str++)
        hash += c;

    return hash;
} */
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char *buf = "Hello World!";
    
    printf("BKDRHash %lu\n", BKDRHash(buf));
    printf("SDBMHash %lu\n", SDBMHash(buf));
    printf("RSHash %lu\n", RSHash(buf));
    printf("APHash %lu\n", APHash(buf));
    printf("JSHash %lu\n", JSHash(buf));
    printf("DEKHash %lu\n", DEKHash(buf));
    printf("FNVHash %lu\n", FNVHash(buf));
    printf("DJBHash %lu\n", DJBHash(buf));
    printf("DJB2Hash %lu\n", DJB2Hash(buf));
    //printf("DJB2Hash_2 %lu\n", DJB2Hash_2((unsigned char *)buf));
    printf("PJWHash %lu\n", PJWHash(buf));
    printf("ELFHash %lu\n", ELFHash(buf));
    //printf("lose_lose_hash %lu\n", lose_lose_hash((unsigned char *)buf));
    return 0;
}