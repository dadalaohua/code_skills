#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//https://elixir.bootlin.com/linux/v3.10.108/source/include/linux/hash.h

uint64_t hash_64(uint64_t val) {
    uint64_t hash = val;

    /*  Sigh, gcc can't optimise this alone like it does for 32 bits. */
    uint64_t n = hash;
    n <<= 18;
    hash -= n;
    n <<= 33;
    hash -= n;
    n <<= 3;
    hash += n;
    n <<= 3;
    hash -= n;
    n <<= 4;
    hash += n;
    n <<= 2;
    hash += n;

    return hash;
}

//https://elixir.bootlin.com/linux/v5.17.3/source/include/linux/hash.h

#define GOLDEN_RATIO_64 0x61C8864680B583EBull

uint64_t hash_64_2(uint64_t val) {
    /* 64x64-bit multiply is efficient on all 64-bit processors */
    return val * GOLDEN_RATIO_64;
}

//64 bit Mix Functions
uint64_t hash64shift(uint64_t key) {
    key = (~key) + (key << 21); // key = (key << 21) - key - 1;
    key = key ^ (key >> 24);
    key = (key + (key << 3)) + (key << 8); // key * 265
    key = key ^ (key >> 14);
    key = (key + (key << 2)) + (key << 4); // key * 21
    key = key ^ (key >> 28);
    key = key + (key << 31);
    return key;
}

//https://qastack.cn/programming/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
uint64_t ABChash64(uint64_t x) {
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ull;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebull;
    x = x ^ (x >> 31);
    return x;
}

uint64_t ABCunhash64(uint64_t x) {
    x = (x ^ (x >> 31) ^ (x >> 62)) * 0x319642b2d24d8ec3ull;
    x = (x ^ (x >> 27) ^ (x >> 54)) * 0x96de1b173f119089ull;
    x = x ^ (x >> 30) ^ (x >> 60);
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
        printf("%3d : %20lu %016lx %3ld\n", i, hash_64(i), hash_64(i), hash_64(i)%100);
    }
    printf("\n");
    
    //linux 5.17
    printf("linux 5.17:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %20lu %016lx %3ld\n", i, hash_64(i), hash_64(i), hash_64(i)%100);
    }
    printf("\n");
    
    //64 bit Mix Functions
    printf("64 bit Mix Functions:\n");
    for(int i = 0; i < 100; i++) {
        printf("%3d : %20lu %016lx %3ld\n", i, hash64shift(i), hash64shift(i), hash64shift(i)%100);
    }
    printf("\n");

    
    //https://qastack.cn/programming/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
    for(int i = 0; i < 100; i++) {
        printf("%3d : %20lu %016lx %3lu %3ld\n", i, ABChash64(i), ABChash64(i), ABCunhash64(ABChash64(i)), ABChash64(i)%100);
    }
    printf("\n");
    
    return 0;
}