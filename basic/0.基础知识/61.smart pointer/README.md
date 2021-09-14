# smart pointer

```
ubuntu_test/1.test/91.smart pointer$ make
cc    -c -o test_code.o test_code.c
gcc -o test_code test_code.c -Wall
ubuntu_test/1.test/91.smart pointer$ valgrind ./test_code
==7999== Memcheck, a memory error detector
==7999== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==7999== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==7999== Command: ./test_code
==7999==
==7999== error calling PR_SET_PTRACER, vgdb might block
==7999==
==7999== HEAP SUMMARY:
==7999==     in use at exit: 0 bytes in 0 blocks
==7999==   total heap usage: 1 allocs, 1 frees, 20 bytes allocated
==7999==
==7999== All heap blocks were freed -- no leaks are possible
==7999==
==7999== For lists of detected and suppressed errors, rerun with: -s
==7999== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

https://snai.pe/posts/c-smart-pointers
