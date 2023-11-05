#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <spawn.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//程序运行的环境变量
extern char **environ;
/************************************************************************/
/*                                                                      */
/************************************************************************/
void test_posix_spawn(void)
{
    pid_t  nPid;
    posix_spawnattr_t attr;  
    posix_spawn_file_actions_t file_actions;
    char* arg[] = {"/bin/ps", "-lf", NULL};
    char* envp[] = {NULL};
  
    posix_spawnattr_init(&attr);
    posix_spawn_file_actions_init(&file_actions);
  
    posix_spawn(&nPid, "/bin/ps", &file_actions, &attr, arg, envp);

    printf("spawned PID %d\n", nPid);
}

void test_posix_spawnp(void)
{
    pid_t  nPid;
    posix_spawnattr_t attr;  
    posix_spawn_file_actions_t file_actions;
    char* arg[] = {"/bin/ls", "-l", NULL};
    char* envp[] = {NULL};
  
    posix_spawnattr_init(&attr);
    posix_spawn_file_actions_init(&file_actions);
  
    posix_spawnp(&nPid, "ls", &file_actions, &attr, arg, envp);

    printf("spawned PID %d\n", nPid);
}

//子进程使用父进程的环境变量。当程序启动时，会复制，父进程的环境变量
void test_posix_spawn_2(void)
{
    pid_t  nPid;
    posix_spawnattr_t attr;  
    posix_spawn_file_actions_t file_actions;
    char* arg[] = {"/bin/ps", "-lf", NULL};
    
    posix_spawnattr_init(&attr);
    posix_spawn_file_actions_init(&file_actions);
    
    //使用 environ
    posix_spawn(&nPid, "/bin/ps", &file_actions, &attr, arg, environ);

    printf("spawned PID %d\n", nPid);
}

int main(int argc, char* argv[])
{
    test_posix_spawn();
    test_posix_spawnp();
    
    test_posix_spawn_2();
    
    return 0;
}