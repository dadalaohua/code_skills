#include <stdio.h>
#include <sys/sysinfo.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int cpu_total;
    int cpu_num;
    
    cpu_total = get_nprocs_conf();  //返回CPU总核数，包括系统中禁用的核的数目，因此该值并不代表当前系统中可用的核数。
    cpu_num = get_nprocs(); //返回系统当前可用的核数
    
    printf("cpu total: %d\n", cpu_total);
    printf("cpu num: %d\n", cpu_num);

    return 0;
}