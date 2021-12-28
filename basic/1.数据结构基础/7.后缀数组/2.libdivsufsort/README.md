# libdivsufsort

https://github.com/y-256/libdivsufsort

libdivsufsort is a software library that implements a lightweight suffix array construction algorithm.

libdivsufsort 是一个实现轻量级后缀数组构造算法的软件库。

This library provides a simple and an efficient C API to construct a suffix array and a Burrows-Wheeler transformed string from a given string over a constant-size alphabet. The algorithm runs in O(n log n) worst-case time using only 5n+O(1) bytes of memory space, where n is the length of the string.

这个库提供了一个简单而有效的C API来构造后缀数组和Burrows-Wheeler转换后的字符串，该字符串由给定的字符串按照恒定大小的字母表组成。算法在最坏情况下运行时间为O(n log n)，只使用了5n+O(1)字节的内存空间，其中n是字符串的长度。

## API

```
/* Data types */
typedef int32_t saint_t;
typedef int32_t saidx_t;
typedef uint8_t sauchar_t;

/*
 * Constructs the suffix array of a given string.
 * @param T[0..n-1] The input string.
 * @param SA[0..n-1] The output array or suffixes.
 * @param n The length of the given string.
 * @return 0 if no error occurred, -1 or -2 otherwise.
 */
saint_t
divsufsort(const sauchar_t *T, saidx_t *SA, saidx_t n);

/*
 * Constructs the burrows-wheeler transformed string of a given string.
 * @param T[0..n-1] The input string.
 * @param U[0..n-1] The output string. (can be T)
 * @param A[0..n-1] The temporary array. (can be NULL)
 * @param n The length of the given string.
 * @return The primary index if no error occurred, -1 or -2 otherwise.
 */
saidx_t
divbwt(const sauchar_t *T, sauchar_t *U, saidx_t *A, saidx_t n);
```

## Example Usage

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <divsufsort.h>

int main() {
    // intput data
    char *Text = "abracadabra";
    int n = strlen(Text);
    int i, j;

    // allocate
    int *SA = (int *)malloc(n * sizeof(int));

    // sort
    divsufsort((unsigned char *)Text, SA, n);

    // output
    for(i = 0; i < n; ++i) {
        printf("SA[%2d] = %2d: ", i, SA[i]);
        for(j = SA[i]; j < n; ++j) {
            printf("%c", Text[j]);
        }
        printf("$\n");
    }

    // deallocate
    free(SA);

    return 0;
}
```

See the [examples](https://github.com/y-256/libdivsufsort/blob/master/examples) directory for a few other examples.



***

```
@DESKTOP:/mnt/libdivsufsort/build$ cmake -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX="/mnt/libdivsufsort/local" ..
-- The C compiler identification is GNU 9.3.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Performing Test HAVE_GCC_WALL
-- Performing Test HAVE_GCC_WALL - Success
-- Performing Test HAVE_GCC_FOMIT_FRAME_POINTER
-- Performing Test HAVE_GCC_FOMIT_FRAME_POINTER - Success
-- Looking for inttypes.h
-- Looking for inttypes.h - found
-- Looking for memory.h
-- Looking for memory.h - found
-- Looking for stddef.h
-- Looking for stddef.h - found
-- Looking for stdint.h
-- Looking for stdint.h - found
-- Looking for stdlib.h
-- Looking for stdlib.h - found
-- Looking for string.h
-- Looking for string.h - found
-- Looking for strings.h
-- Looking for strings.h - found
-- Looking for sys/types.h
-- Looking for sys/types.h - found
-- Check size of off_t
-- Check size of off_t - done
-- Looking for fseeko
-- Looking for fseeko - found
-- Looking for ftello
-- Looking for ftello - found
-- Looking for PRIdMAX
-- Looking for PRIdMAX - found
-- Performing Test HAVE_INLINE
-- Performing Test HAVE_INLINE - Success
-- Performing Test HAVE___INLINE
-- Performing Test HAVE___INLINE - Success
-- Performing Test HAVE___INLINE__
-- Performing Test HAVE___INLINE__ - Success
-- Performing Test HAVE___DECLSPEC_DLLEXPORT_
-- Performing Test HAVE___DECLSPEC_DLLEXPORT_ - Failed
-- Performing Test HAVE___DECLSPEC_DLLIMPORT_
-- Performing Test HAVE___DECLSPEC_DLLIMPORT_ - Failed
-- Check size of uint8_t
-- Check size of uint8_t - done
-- Check size of int32_t
-- Check size of int32_t - done
-- Looking for PRId32
-- Looking for PRId32 - found
-- Configuring done
-- Generating done
-- Build files have been written to: /mnt/libdivsufsort/build
@DESKTOP:/mnt/libdivsufsort/build$
@DESKTOP:/mnt/libdivsufsort/build$ make
Scanning dependencies of target divsufsort
[  6%] Building C object lib/CMakeFiles/divsufsort.dir/divsufsort.o
[ 13%] Building C object lib/CMakeFiles/divsufsort.dir/sssort.o
[ 20%] Building C object lib/CMakeFiles/divsufsort.dir/trsort.o
[ 26%] Building C object lib/CMakeFiles/divsufsort.dir/utils.o
[ 33%] Linking C shared library libdivsufsort.so
[ 33%] Built target divsufsort
Scanning dependencies of target unbwt
[ 40%] Building C object examples/CMakeFiles/unbwt.dir/unbwt.o
[ 46%] Linking C executable unbwt
[ 46%] Built target unbwt
Scanning dependencies of target sasearch
[ 53%] Building C object examples/CMakeFiles/sasearch.dir/sasearch.o
[ 60%] Linking C executable sasearch
[ 60%] Built target sasearch
Scanning dependencies of target mksary
[ 66%] Building C object examples/CMakeFiles/mksary.dir/mksary.o
[ 73%] Linking C executable mksary
[ 73%] Built target mksary
Scanning dependencies of target bwt
[ 80%] Building C object examples/CMakeFiles/bwt.dir/bwt.o
[ 86%] Linking C executable bwt
[ 86%] Built target bwt
Scanning dependencies of target suftest
[ 93%] Building C object examples/CMakeFiles/suftest.dir/suftest.o
[100%] Linking C executable suftest
[100%] Built target suftest
@DESKTOP:/mnt/libdivsufsort/build$
```

