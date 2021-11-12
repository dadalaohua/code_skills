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

int main(int argc, char* argv[])
{
    pid_t  nPid;
    posix_spawnattr_t attr;  
    posix_spawn_file_actions_t file_actions;
    char* arg[] = {"/bin/ps", "-lf", NULL};
    char* envp[] = {"PROCESS=2"};
  
    posix_spawnattr_init(&attr);
    posix_spawn_file_actions_init(&file_actions);
  
    posix_spawn(&nPid, "/bin/ps", &file_actions, &attr, arg, envp);

    printf("spawned PID %d\n", nPid);
    
    return 0;
}