
/* 
How To Use
1. Please #undef macros MFUNC_IN_START and MFUNC_IN_DELTA before using
2. [optional]Define macro MFUNC_IN_START to specify the starting value
3. [optional]Define macro MFUNC_IN_DELTA to specify the increasing step
4. Define macro MFUNC_IN_COUNT to specify the number of items. 

NOTE: the MFUNC_IN_COUNT should not larger than 200

// 4位 Alpha 对应 8bit Alpha的备查表
const uint8_t c_chAlphaA4Table[16] = {

#undef MFUNC_IN_START
#undef MFUNC_IN_DELTA

#define MFUNC_IN_START    0
#define MFUNC_IN_COUNT    16
#define MFUNC_IN_DELTA    17
#include "mf_u8_fill_dec.h"

};
*/

#ifndef MFUNC_IN_START   
#   define MFUNC_IN_START    0    /* 默认从 0 开始 */
#endif
#ifndef MFUNC_IN_DELTA
#   define MFUNC_IN_DELTA    1    /* 默认以 1 为间隔 */
#endif
#ifndef MFUNC_IN_COUNT
/* 连数量都不提供，这就不能忍了！*/
#    error "Please at least define MFUNC_COUNT!!!"
#endif

/* 如果计数器为0就退出 */
#if MFUNC_IN_COUNT

/* 实现 MFUNC_IN_COUNT-- */
// MFUNC_IN_U8_DEC_VALUE = MFUNC_IN_COUNT - 1; 给脚本提供输入
#define MFUNC_IN_U8_DEC_VALUE    (MFUNC_IN_COUNT - 1)
#include "mf_u8_dec2str.h"
#undef MFUNC_IN_COUNT
//! MFUNC_IN_COUNT = MFUNC_OUT_DEC_STR; 获得脚本输出
#define MFUNC_IN_COUNT    MFUNC_OUT_DEC_STR

#include "mf_u8_fill_dec.h"


/* Loop body begin ------------------------------- */
MFUNC_IN_START,

/* 实现 FUNC_IN_START += FUNC_IN_DELTA */
#define MFUNC_IN_U8_DEC_VALUE    (MFUNC_IN_START + MFUNC_IN_DELTA)
#include "mf_u8_dec2str.h"
#undef MFUNC_IN_START
#define MFUNC_IN_START    MFUNC_OUT_DEC_STR

/* Loop body End --------------------------------- */

#endif

#undef MFUNC_IN_COUNT