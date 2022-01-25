#ifndef __FUNC_WRAP_H_
#define __FUNC_WRAP_H_
/************************************************************************/
/*                                                                      */
/************************************************************************/
// 函数“重导向”，这样的话 app.c 中才能调用 wrap_rd3_func
#define magicfunc()   wrap_magicfunc()

extern void wrap_magicfunc(void);

/****************************/
#endif