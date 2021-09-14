# libcsptr

```
ubuntu_test/1.test/92.libcsptr$ make
gcc -I./include/csptr -o test_code test_code.c ./src/mman.c ./src/array.c -Wall
ubuntu_test/1.test/92.libcsptr$ valgrind ./test_code
==8045== Memcheck, a memory error detector
==8045== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==8045== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==8045== Command: ./test_code
==8045==
==8045== error calling PR_SET_PTRACER, vgdb might block
0x4a47060 = 1
1
2
3
4
5
==8045==
==8045== HEAP SUMMARY:
==8045==     in use at exit: 0 bytes in 0 blocks
==8045==   total heap usage: 6 allocs, 6 frees, 4,344 bytes allocated
==8045==
==8045== All heap blocks were freed -- no leaks are possible
==8045==
==8045== For lists of detected and suppressed errors, rerun with: -s
==8045== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

https://snai.pe/posts/c-smart-pointers

https://github.com/Snaipe/libcsptr
