#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("%zd\n", sizeof(int8_t));        //8-bit signed type.
    printf("%zd\n", sizeof(int_fast8_t));   //fastest signed int with at least 8 bits.
    printf("%zd\n", sizeof(int_least8_t));  //signed int with at least 8 bits.
    printf("\n");
    
    printf("%zd\n", sizeof(int16_t));       //16-bit signed type.
    printf("%zd\n", sizeof(int_fast16_t));  //fastest signed int with at least 16 bits.
    printf("%zd\n", sizeof(int_least16_t)); //signed int with at least 16 bits.
    printf("\n");
    
    printf("%zd\n", sizeof(int32_t));       //32-bit signed type.
    printf("%zd\n", sizeof(int_fast32_t));  //fastest signed int with at least 32 bits.
    printf("%zd\n", sizeof(int_least32_t)); //signed int with at least 32 bits.
    printf("\n");
    
    printf("%zd\n", sizeof(int64_t));       //64-bit signed type.
    printf("%zd\n", sizeof(int_fast64_t));  //fastest signed int with at least 64 bits.
    printf("%zd\n", sizeof(int_least64_t)); //signed int with at least 64 bits.
    printf("\n");
    
    printf("%zd\n", sizeof(uint8_t));       //8-bit unsigned type.
    printf("%zd\n", sizeof(uint_fast8_t));  //fastest unsigned int with at least 8 bits.
    printf("%zd\n", sizeof(uint_least8_t)); //unsigned int with at least 8 bits.
    printf("\n");
    
    printf("%zd\n", sizeof(uint16_t));          //16-bit unsigned type.
    printf("%zd\n", sizeof(uint_fast16_t));     //fastest unsigned int with at least 16 bits.
    printf("%zd\n", sizeof(uint_least16_t));    //unsigned int with at least 16 bits.
    printf("\n");
    
    printf("%zd\n", sizeof(uint32_t));          //32-bit unsigned type.
    printf("%zd\n", sizeof(uint_fast32_t));     //fastest unsigned int with at least 32 bits.
    printf("%zd\n", sizeof(uint_least32_t));    //unsigned int with at least 32 bits.
    printf("\n");
    
    printf("%zd\n", sizeof(uint64_t));          //64-bit unsigned type.
    printf("%zd\n", sizeof(uint_fast64_t));     //fastest unsigned int with at least 64 bits.
    printf("%zd\n", sizeof(uint_least64_t));    //unsigned int with at least 64 bits.
    printf("\n");
    
    printf("%zd\n", sizeof(intmax_t));      //largest signed int available.
    printf("%zd\n", sizeof(uintmax_t));     //largest unsigned int available.
    printf("\n");
    
    printf("%zd\n", sizeof(intptr_t));      //Signed pointer compatible type.
    printf("%zd\n", sizeof(uintptr_t));     //Unsigned pointer compatible type.
    printf("\n");
    
    printf("%d\n", INT8_MAX);   //largest positive value an int8_t can hold.
    printf("%d\n", INT8_MIN);   //smallest negative value an int8_t can hold.
    printf("\n");
    
    printf("%d\n", INT16_MAX);  //largest positive value an int16_t can hold.
    printf("%d\n", INT16_MIN);  //smallest negative value an int16_t can hold.
    printf("\n");
    
    printf("%d\n", INT32_MAX);  //largest positive value an int32_t can hold.
    printf("%d\n", INT32_MIN);  //smallest negative value an int32_t can hold.
    printf("\n");
    
    printf("%ld\n", INT64_MAX);  //largest positive value an int64_t can hold.
    printf("%ld\n", INT64_MIN);  //smallest negative value an int64_t can hold.
    printf("\n");
    
    printf("%d\n", INT_FAST8_MAX);   //largest positive value an int_fast8_t can hold.
    printf("%d\n", INT_FAST8_MIN);   //smallest negative value an int_fast8_t can hold.
    printf("\n");
    
    printf("%ld\n", INT_FAST16_MAX); //largest positive value an int_fast16_t can hold.
    printf("%ld\n", INT_FAST16_MIN);  //smallest negative value an int_fast16_t can hold.
    printf("\n");
    
    printf("%ld\n", INT_FAST32_MAX);  //largest positive value an int_fast32_t can hold.
    printf("%ld\n", INT_FAST32_MIN);  //smallest negative value an int_fast32_t can hold.
    printf("\n");
    
    printf("%ld\n", INT_FAST64_MAX);  //largest positive value an int_fast64_t can hold.
    printf("%ld\n", INT_FAST64_MIN);  //smallest negative value an int_fast64_t can hold.
    printf("\n");
    
    printf("%d\n", INT_LEAST8_MAX);   //largest positive value an int_least8_t can hold.
    printf("%d\n", INT_LEAST8_MIN);   //smallest negative value an int_least8_t can hold.
    printf("\n");
    
    printf("%d\n", INT_LEAST16_MAX);    //largest positive value an int_least16_t can hold.
    printf("%d\n", INT_LEAST16_MIN);    //smallest negative value an int_least16_t can hold.
    printf("\n");
    
    printf("%d\n", INT_LEAST32_MAX);  //largest positive value an int_least32_t can hold.
    printf("%d\n", INT_LEAST32_MIN);  //smallest negative value an int_least32_t can hold.
    printf("\n");
    
    printf("%ld\n", INT_LEAST64_MAX);  //largest positive value an int_least64_t can hold.
    printf("%ld\n", INT_LEAST64_MIN);  //smallest negative value an int_least64_t can hold.
    printf("\n");
    
    printf("%ld\n", INTMAX_MAX);    //largest positive value an intmax_t can hold.
    printf("%ld\n", INTMAX_MIN);    //smallest negative value an intmax_t can hold.
    printf("\n");
    
    printf("%ld\n", INTPTR_MAX);    //largest positive value an intptr_t can hold.
    printf("%ld\n", INTPTR_MIN);    //smallest negative value an intptr_t can hold.
    printf("\n");
    
    printf("%ld\n", PTRDIFF_MAX);   //largest positive value a ptrdiff_t can hold.
    printf("%ld\n", PTRDIFF_MIN);   //smallest negative value a ptrdiff_t can hold.
    printf("\n");
    
    printf("%d\n", SIG_ATOMIC_MAX); //largest positive value a sig_atomic_t can hold.
    printf("%d\n", SIG_ATOMIC_MIN); //smallest negative value a sig_atomic_t can hold.
    printf("\n");
    
    printf("%zu\n", SIZE_MAX);  //largest value a size_t can hold.
    printf("\n");
    
    printf("%u\n", UINT8_MAX);     //largest value an uint8_t can hold.
    printf("\n");
    
    printf("%u\n", UINT16_MAX);    //largest value an uint16_t can hold.
    printf("\n");
    
    printf("%u\n", UINT32_MAX);    //largest value an uint32_t can hold.
    printf("\n");
    
    printf("%zu\n", UINT64_MAX);    //largest value an uint64_t can hold.
    printf("\n");
    
    printf("%u\n", UINT_FAST8_MAX);     //largest value an uint_fast8_t can hold.
    printf("\n");
    
    printf("%lu\n", UINT_FAST16_MAX);    //largest value an uint_fast16_t can hold.
    printf("\n");
    
    printf("%lu\n", UINT_FAST32_MAX);    //largest value an uint_fast32_t can hold.
    printf("\n");
    
    printf("%zu\n", UINT_FAST64_MAX);   //largest value an uint_fast64_t can hold.
    printf("\n");
    
    printf("%u\n", UINT_LEAST8_MAX);     //largest value an uint_least8_t can hold.
    printf("\n");
    
    printf("%u\n", UINT_LEAST16_MAX);    //largest value an uint_least16_t can hold.
    printf("\n");
    
    printf("%u\n", UINT_LEAST32_MAX);    //largest value an uint_least32_t can hold.
    printf("\n");
    
    printf("%zu\n", UINT_LEAST64_MAX);   //largest value an uint_least64_t can hold.
    printf("\n");
    
    printf("%lu\n", UINTMAX_MAX);    //largest value an uintmax_t can hold.
    printf("\n");
    
    printf("%zu\n", UINTPTR_MAX);   //largest value an uintptr_t can hold.
    printf("\n");
    
    return 0;
}