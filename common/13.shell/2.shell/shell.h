#ifndef __SHELL_H__
#define __SHELL_H__

#define MATCH_CASE_ENABLE     0             //函数调用名称大小写是否敏感 1表示敏感 0 表示不敏感

typedef struct
{
    const char * FuncName;
    void *( (*func)(void* args,...));
    const char * fmt;
    const char * Introduction;
} CALLFUNCTIONTABLE;

#define EXPOTRFUNC(NAME,FUNC,FTM,INTRO) {#NAME,(void *(*)(void* args,...))FUNC,#FTM,#INTRO}

extern const CALLFUNCTIONTABLE functable[];

void ExternFunc_excute(char* str);

void show(int i);
void showcircle(char ch,int r);
void simplefunction(char* str,unsigned int sum,float dee,char ch);
void ExternFunc_list(void);

#endif //__SHELL_H__
