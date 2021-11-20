#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <spawn.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

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

int main(int argc, char* argv[])
{
    test_posix_spawn();
    test_posix_spawnp();
    
    return 0;
}