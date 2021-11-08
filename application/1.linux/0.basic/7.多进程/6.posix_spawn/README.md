# posix_spawn

https://blog.csdn.net/linux_ever/article/details/50295105

```c
 #include <spawn.h>
 int posix_spawn(pid_t *restrict pid, const char *restrict path,
        const posix_spawn_file_actions_t *file_actions,
        const posix_spawnattr_t *restrict attrp,
        char *const argv[restrict], char *const envp[restrict]);
```

在main函数中调用该函数可以将一个可执行文件运行起来；如下面所示：
posix_spawn(&child_pid, "ls", NULL, NULL, argv, NULL);
执行完该函数之后，会将该目录下的ls可执行程序运行起来，会输出该目录下的文件；
argv参数可有可无，在例子中，如果没有带参数，那么直接执行ls；也可以带上参数-l,那么直接执行ls -l,则以列表的形式显示该目录下的文件。
