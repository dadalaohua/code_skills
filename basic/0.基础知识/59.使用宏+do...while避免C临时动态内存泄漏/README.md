# 使用宏+do...while避免C临时动态内存泄漏

达到类似using的效果

```
ubuntu_test/1.test/93.test$ make
cc    -c -o test_code.o test_code.c
gcc -o test_code test_code.c -Wall
ubuntu_test/1.test/93.test$ valgrind ./test_code
==7969== Memcheck, a memory error detector
==7969== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==7969== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==7969== Command: ./test_code
==7969==
==7969== error calling PR_SET_PTRACER, vgdb might block
buf 5
buf->a 5
buf->b[0] 10
buf->b[1] 11
buf->b[2] 12
buf->b[3] 13
buf->b[4] 14
==7969==
==7969== HEAP SUMMARY:
==7969==     in use at exit: 0 bytes in 0 blocks
==7969==   total heap usage: 3 allocs, 3 frees, 4,109 bytes allocated
==7969==
==7969== All heap blocks were freed -- no leaks are possible
==7969==
==7969== For lists of detected and suppressed errors, rerun with: -s
==7969== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

http://blog.chinaunix.net/uid-26904464-id-5103200.html
