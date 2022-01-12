#include <stdio.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct static_cmd_function_struct
{
    const char *cmd;
    void (*fp)(void);
    char *description;
}__attribute__ ((aligned (16))) static_cmd_st;
 
#define NR_USED __attribute__((used))
#define NR_SECTION(x) __attribute__((section(".rodata_nr_shell_cmd" x)))
#define NR_SHELL_CMD_EXPORT_START(cmd, func) \
    NR_USED const static_cmd_st _nr_cmd_start_ NR_SECTION("_start") = {#cmd, NULL}
#define NR_SHELL_CMD_EXPORT(cmd, func) \
    NR_USED const static_cmd_st _nr_cmd_##cmd NR_SECTION("") = {#cmd, func}
#define NR_SHELL_CMD_EXPORT_END(cmd, func) \
    NR_USED const static_cmd_st _nr_cmd_end_ NR_SECTION("_end") = {#cmd, NULL}

NR_SHELL_CMD_EXPORT_START(start,NULL);
NR_SHELL_CMD_EXPORT_END(end,NULL);

static void func1(void)
{
    printf("call %s\n", __FUNCTION__);
}

NR_SHELL_CMD_EXPORT(ls, func1);
 
static void func2(void)
{
    printf("call %s\n", __FUNCTION__);
}

NR_SHELL_CMD_EXPORT(ls2, func2);

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    const static_cmd_st *p0 = &_nr_cmd_start_, *p1 = &_nr_cmd_ls, *p2 = &_nr_cmd_ls2, *p3 = &_nr_cmd_end_;

    printf("sizeof=0x%lx\r\n", sizeof(static_cmd_st));
    printf("addr:p0 %p\r\n", p0);
    printf("addr:p1 %p\r\n", p1);
    printf("addr:p2 %p\r\n", p2);
    printf("addr:p3 %p\r\n", p3);

    for(const static_cmd_st *p = &_nr_cmd_start_ + 1; p < &_nr_cmd_end_; p++)
        p->fp();
    
    return 0;
}