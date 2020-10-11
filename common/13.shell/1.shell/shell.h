#ifndef __SHELL_H__
#define __SHELL_H__

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;
typedef signed char         s8;
typedef short               s16;
typedef int                 s32;
typedef long long           s64;

typedef u8  uint8_t;
typedef u16 uint16_t;
typedef u32 uint32_t;
typedef u64 uint64_t;
typedef s8  int8_t;
typedef s16 int16_t;
typedef s32 int32_t;
typedef s64 int64_t;

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define SHELL_LINE_MAX_LEN  100
#define SHELL_PARAM_MAX_NUM 10

typedef int (*T_ShellFun)(int argc, char*argv[]);

typedef struct
{
    char* name; /*命令的名字*/
    char* help; /*帮助描述*/
    T_ShellFun fun; /*命令函数*/
}T_ShellCmd;

extern T_ShellCmd *sysCmd[];

uint8_t shellMain(void);
int shellStr2Int(const char *str, uint8_t* ok);
float shellStr2Float(const char *str, uint8_t* ok);
int shellStr2Hex(const char *str, uint8_t* ok);

#endif
