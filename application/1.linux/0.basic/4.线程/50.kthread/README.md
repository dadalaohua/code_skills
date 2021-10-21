# Kthread: simple threading models

http://attractivechaos.github.io/klib/#Kthread%3A%20simple%20threading%20models

https://github.com/attractivechaos/klib

## Synopsis

- Functionality: simple multi-threading models.
  - kt_for(): parallelize a `for` loop, similar to [clik_for](http://faculty.knox.edu/dbunde/teaching/cilk/#cilk_for).
  - kt_pipeline(): parallelize a repeated multi-step pipeline with each step possibly on different threads.
- Library source code: [kthread.c](https://github.com/attractivechaos/klib/blob/master/kthread.c)
- Dependencies: [POSIX thread](http://en.wikipedia.org/wiki/Native_POSIX_Thread_Library)
- Example program: [kthread_test.c](https://github.com/attractivechaos/klib/blob/master/test/kthread_test.c) and [kthread_test2.c](https://github.com/attractivechaos/klib/blob/master/test/kthread_test2.c)
- Blog post: [Parallelize simple for loops](https://attractivechaos.wordpress.com/2013/10/11/parallelizing-simple-for-loops/)

