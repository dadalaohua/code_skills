# autofree

```
ubuntu_test/1.test/90.autofree$ make
cc    -c -o test_code.o test_code.c
gcc -o test_code test_code.c -Wall
ubuntu_test/1.test/90.autofree$ valgrind ./test_code
==7984== Memcheck, a memory error detector
==7984== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==7984== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==7984== Command: ./test_code
==7984==
==7984== error calling PR_SET_PTRACER, vgdb might block
==7984==
==7984== HEAP SUMMARY:
==7984==     in use at exit: 0 bytes in 0 blocks
==7984==   total heap usage: 1 allocs, 1 frees, 4 bytes allocated
==7984==
==7984== All heap blocks were freed -- no leaks are possible
==7984==
==7984== For lists of detected and suppressed errors, rerun with: -s
==7984== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

https://snai.pe/posts/c-smart-pointers
