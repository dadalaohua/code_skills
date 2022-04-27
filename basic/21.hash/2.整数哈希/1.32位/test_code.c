#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//https://elixir.bootlin.com/linux/v3.10.108/source/include/linux/hash.h

/* 2^31 + 2^29 - 2^25 + 2^22 - 2^19 - 2^16 + 1 */
#define GOLDEN_RATIO_PRIME_32 0x9e370001UL

uint32_t hash_32(uint32_t val) {
    /* On some cpus multiply is faster, on others gcc will do shifts */
    uint32_t hash = val * GOLDEN_RATIO_PRIME_32;
    
    return hash;
}

//https://elixir.bootlin.com/linux/v5.17.3/source/include/linux/hash.h

#define GOLDEN_RATIO_32 0x61C88647

uint32_t hash_32_2(uint32_t val) {
    uint32_t hash = val * GOLDEN_RATIO_32;
    
    return hash;
}

//Knuth's Multiplicative Method
uint32_t Knuth_hash_32(uint32_t val) {
    
    uint32_t hash = val * 2654435761;
    
    return hash;
}

//Thomas Wang's 32 bit Mix Function
uint32_t Thomas_Wang_hash_32(uint32_t key) {
    key = ~key + (key << 15); // key = (key << 15) - key - 1;
    key = key ^ (key >> 12);
    key = key + (key << 2);
    key = key ^ (key >> 4);
    key = key * 2057; // key = (key + (key << 3)) + (key << 11);
    key = key ^ (key >> 16);
    return key;
}

//Robert Jenkins' 32 bit integer hash function
uint32_t Robert_Jenkins_hash(uint32_t a)
{
    a = (a+0x7ed55d16) + (a<<12);
    a = (a^0xc761c23c) ^ (a>>19);
    a = (a+0x165667b1) + (a<<5);
    a = (a+0xd3a2646c) ^ (a<<9);
    a = (a+0xfd7046c5) + (a<<3);
    a = (a^0xb55a4f09) ^ (a>>16);
    return a;
}

//https://qastack.cn/programming/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
uint32_t ABChash(uint32_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

uint32_t ABCunhash(uint32_t x) {
    x = ((x >> 16) ^ x) * 0x119de1f3;
    x = ((x >> 16) ^ x) * 0x119de1f3;
    x = (x >> 16) ^ x;
    return x;
}

//https://github.com/skeeto/hash-prospector
// exact bias: 0.17353355999581582
uint32_t lowbias32(uint32_t x)
{
    x ^= x >> 16;
    x *= 0x7feb352d;
    x ^= x >> 15;
    x *= 0x846ca68b;
    x ^= x >> 16;
    return x;
}

// inverse
uint32_t lowbias32_r(uint32_t x)
{
    x ^= x >> 16;
    x *= 0x43021123;
    x ^= x >> 15 ^ x >> 30;
    x *= 0x1d69e2a5;
    x ^= x >> 16;
    return x;
}

//https://github.com/skeeto/hash-prospector
// exact bias: 0.020888578919738908
uint32_t triple32(uint32_t x)
{
    x ^= x >> 17;
    x *= 0xed5ad4bb;
    x ^= x >> 11;
    x *= 0xac4c1b51;
    x ^= x >> 15;
    x *= 0x31848bab;
    x ^= x >> 14;
    return x;
}

// inverse
uint32_t triple32_r(uint32_t x)
{
    x ^= x >> 14 ^ x >> 28;
    x *= 0x32b21703;
    x ^= x >> 15 ^ x >> 30;
    x *= 0x469e0db1;
    x ^= x >> 11 ^ x >> 22;
    x *= 0x79a85073;
    x ^= x >> 17;
    return x;
}

//https://github.com/skeeto/hash-prospector
// exact bias: 0.020829410544597495
uint32_t triple32inc(uint32_t x)
{
    x++;
    x ^= x >> 17;
    x *= 0xed5ad4bb;
    x ^= x >> 11;
    x *= 0xac4c1b51;
    x ^= x >> 15;
    x *= 0x31848bab;
    x ^= x >> 14;
    return x;
}

// inverse
uint32_t triple32inc_r(uint32_t x)
{
    x ^= x >> 14 ^ x >> 28;
    x *= 0x32b21703;
    x ^= x >> 15 ^ x >> 30;
    x *= 0x469e0db1;
    x ^= x >> 11 ^ x >> 22;
    x *= 0x79a85073;
    x ^= x >> 17;
    x--;
    return x;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    //linux 3.10
    printf("linux 3.10:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %10u %08x %3d\n", i, hash_32(i), hash_32(i), hash_32(i)%100);
    }
    printf("\n");
    
    //linux 5.17
    printf("linux 5.17:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %10u %08x %3d\n", i, hash_32_2(i), hash_32_2(i), hash_32_2(i)%100);
    }
    printf("\n");
    
    //Knuth's Multiplicative Method
    printf("Knuth's Multiplicative Method:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %10u %08x %3d\n", i, Knuth_hash_32(i), Knuth_hash_32(i), Knuth_hash_32(i)%100);
    }
    printf("\n");
    
    //Thomas Wang's 32 bit Mix Function
    printf("Thomas Wang's 32 bit Mix Function:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %10u %08x %3d\n", i, Thomas_Wang_hash_32(i), Thomas_Wang_hash_32(i), Thomas_Wang_hash_32(i)%100);
    }
    printf("\n");
    
    //Robert Jenkins' 32 bit integer hash function
    printf("Robert Jenkins' 32 bit integer hash function:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %10u %08x %3d\n", i, Robert_Jenkins_hash(i), Robert_Jenkins_hash(i), Robert_Jenkins_hash(i)%100);
    }
    printf("\n");
    
    //https://qastack.cn/programming/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
    for(int i = 0; i < 100; i++) {
        printf("%3d : %10u %08x %10u %3d\n", i, ABChash(i), ABChash(i), ABCunhash(ABChash(i)), ABChash(i)%100);
    }
    printf("\n");
    
    //lowbias32
    printf("lowbias32:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %10u %08x %10u %3d\n", i, lowbias32(i), lowbias32(i), lowbias32_r(lowbias32(i)), lowbias32(i)%100);
    }
    printf("\n");
    
    //triple32
    printf("triple32:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %10u %08x %10u %3d\n", i, triple32(i), triple32(i), triple32_r(triple32(i)), triple32(i)%100);
    }
    printf("\n");
    
    //triple32inc
    printf("triple32inc:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %10u %08x %10u %3d\n", i, triple32inc(i), triple32inc(i), triple32inc_r(triple32inc(i)), triple32inc(i)%100);
    }
    printf("\n");
    
    return 0;
}