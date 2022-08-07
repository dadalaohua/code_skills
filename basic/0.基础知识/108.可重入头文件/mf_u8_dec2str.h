/****************************************************************************
*  Copyright 2020 by Gorgon Meducer (Email:embedded_zhuoran@hotmail.com)    *
*                                                                           *
*  Licensed under the Apache License, Version 2.0 (the "License");          *
*  you may not use this file except in compliance with the License.         *
*  You may obtain a copy of the License at                                  *
*                                                                           *
*     http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                           *
*  Unless required by applicable law or agreed to in writing, software      *
*  distributed under the License is distributed on an "AS IS" BASIS,        *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
*  See the License for the specific language governing permissions and      *
*  limitations under the License.                                           *
*                                                                           *
****************************************************************************/

/*============================ INCLUDES ======================================*/
#include "./connect.h"
/*============================ MACROS ========================================*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MFUNC_IN_U8_DEC_VALUE
#   error Please define the MFUNC_IN_U8_DEC_VALUE as the input value. It must be \
a compile-time constant value.
#endif

#undef __MFUNC_OUT_DEC_DIGIT_TEMP0
#undef __MFUNC_OUT_DEC_DIGIT_TEMP1
#undef __MFUNC_OUT_DEC_DIGIT_TEMP2



#if     (MFUNC_IN_U8_DEC_VALUE % 10) == 0
#   define __MFUNC_OUT_DEC_DIGIT_TEMP0       0
#elif   (MFUNC_IN_U8_DEC_VALUE % 10) == 1
#   define __MFUNC_OUT_DEC_DIGIT_TEMP0       1
#elif   (MFUNC_IN_U8_DEC_VALUE % 10) == 2
#   define __MFUNC_OUT_DEC_DIGIT_TEMP0       2
#elif   (MFUNC_IN_U8_DEC_VALUE % 10) == 3
#   define __MFUNC_OUT_DEC_DIGIT_TEMP0       3
#elif   (MFUNC_IN_U8_DEC_VALUE % 10) == 4
#   define __MFUNC_OUT_DEC_DIGIT_TEMP0       4
#elif   (MFUNC_IN_U8_DEC_VALUE % 10) == 5
#   define __MFUNC_OUT_DEC_DIGIT_TEMP0       5
#elif   (MFUNC_IN_U8_DEC_VALUE % 10) == 6
#   define __MFUNC_OUT_DEC_DIGIT_TEMP0       6
#elif   (MFUNC_IN_U8_DEC_VALUE % 10) == 7
#   define __MFUNC_OUT_DEC_DIGIT_TEMP0       7
#elif   (MFUNC_IN_U8_DEC_VALUE % 10) == 8
#   define __MFUNC_OUT_DEC_DIGIT_TEMP0       8
#elif   (MFUNC_IN_U8_DEC_VALUE % 10) == 9
#   define __MFUNC_OUT_DEC_DIGIT_TEMP0       9
#endif


#if     ((MFUNC_IN_U8_DEC_VALUE/10) % 10) == 0
#   define __MFUNC_OUT_DEC_DIGIT_TEMP1       0
#elif   ((MFUNC_IN_U8_DEC_VALUE/10) % 10) == 1
#   define __MFUNC_OUT_DEC_DIGIT_TEMP1       1
#elif   ((MFUNC_IN_U8_DEC_VALUE/10) % 10) == 2
#   define __MFUNC_OUT_DEC_DIGIT_TEMP1       2
#elif   ((MFUNC_IN_U8_DEC_VALUE/10) % 10) == 3
#   define __MFUNC_OUT_DEC_DIGIT_TEMP1       3
#elif   ((MFUNC_IN_U8_DEC_VALUE/10) % 10) == 4
#   define __MFUNC_OUT_DEC_DIGIT_TEMP1       4
#elif   ((MFUNC_IN_U8_DEC_VALUE/10) % 10) == 5
#   define __MFUNC_OUT_DEC_DIGIT_TEMP1       5
#elif   ((MFUNC_IN_U8_DEC_VALUE/10) % 10) == 6
#   define __MFUNC_OUT_DEC_DIGIT_TEMP1       6
#elif   ((MFUNC_IN_U8_DEC_VALUE/10) % 10) == 7
#   define __MFUNC_OUT_DEC_DIGIT_TEMP1       7
#elif   ((MFUNC_IN_U8_DEC_VALUE/10) % 10) == 8
#   define __MFUNC_OUT_DEC_DIGIT_TEMP1       8
#elif   ((MFUNC_IN_U8_DEC_VALUE/10) % 10) == 9
#   define __MFUNC_OUT_DEC_DIGIT_TEMP1       9
#endif

#if     ((MFUNC_IN_U8_DEC_VALUE/100) % 10) == 0
#   define __MFUNC_OUT_DEC_DIGIT_TEMP2       0
#elif   ((MFUNC_IN_U8_DEC_VALUE/100) % 10) == 1
#   define __MFUNC_OUT_DEC_DIGIT_TEMP2       1
#elif   ((MFUNC_IN_U8_DEC_VALUE/100) % 10) == 2
#   define __MFUNC_OUT_DEC_DIGIT_TEMP2       2
#endif


#undef __MFUNC_OUT_DEC_DIGIT0
#undef __MFUNC_OUT_DEC_DIGIT1
#undef __MFUNC_OUT_DEC_DIGIT2

#if     __MFUNC_OUT_DEC_DIGIT_TEMP0 == 0
#   define __MFUNC_OUT_DEC_DIGIT0       0
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP0 == 1
#   define __MFUNC_OUT_DEC_DIGIT0       1
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP0 == 2
#   define __MFUNC_OUT_DEC_DIGIT0       2
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP0 == 3
#   define __MFUNC_OUT_DEC_DIGIT0       3
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP0 == 4
#   define __MFUNC_OUT_DEC_DIGIT0       4
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP0 == 5
#   define __MFUNC_OUT_DEC_DIGIT0       5
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP0 == 6
#   define __MFUNC_OUT_DEC_DIGIT0       6
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP0 == 7
#   define __MFUNC_OUT_DEC_DIGIT0       7
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP0 == 8
#   define __MFUNC_OUT_DEC_DIGIT0       8
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP0 == 9
#   define __MFUNC_OUT_DEC_DIGIT0       9
#endif

#if     __MFUNC_OUT_DEC_DIGIT_TEMP1 == 0
#   define __MFUNC_OUT_DEC_DIGIT1       0
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP1 == 1
#   define __MFUNC_OUT_DEC_DIGIT1       1
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP1 == 2
#   define __MFUNC_OUT_DEC_DIGIT1       2
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP1 == 3
#   define __MFUNC_OUT_DEC_DIGIT1       3
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP1 == 4
#   define __MFUNC_OUT_DEC_DIGIT1       4
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP1 == 5
#   define __MFUNC_OUT_DEC_DIGIT1       5
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP1 == 6
#   define __MFUNC_OUT_DEC_DIGIT1       6
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP1 == 7
#   define __MFUNC_OUT_DEC_DIGIT1       7
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP1 == 8
#   define __MFUNC_OUT_DEC_DIGIT1       8
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP1 == 9
#   define __MFUNC_OUT_DEC_DIGIT1       9
#endif

#if     __MFUNC_OUT_DEC_DIGIT_TEMP2 == 0
#   define __MFUNC_OUT_DEC_DIGIT2       0
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP2 == 1
#   define __MFUNC_OUT_DEC_DIGIT2       1
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP2 == 2
#   define __MFUNC_OUT_DEC_DIGIT2       2
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP2 == 3
#   define __MFUNC_OUT_DEC_DIGIT2       3
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP2 == 4
#   define __MFUNC_OUT_DEC_DIGIT2       4
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP2 == 5
#   define __MFUNC_OUT_DEC_DIGIT2       5
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP2 == 6
#   define __MFUNC_OUT_DEC_DIGIT2       6
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP2 == 7
#   define __MFUNC_OUT_DEC_DIGIT2       7
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP2 == 8
#   define __MFUNC_OUT_DEC_DIGIT2       8
#elif   __MFUNC_OUT_DEC_DIGIT_TEMP2 == 9
#   define __MFUNC_OUT_DEC_DIGIT2       9
#endif

#undef MFUNC_OUT_DEC_STR
#if __MFUNC_OUT_DEC_DIGIT2 == 0 
#   if __MFUNC_OUT_DEC_DIGIT1 == 0
#       define MFUNC_OUT_DEC_STR        __MFUNC_OUT_DEC_DIGIT0
#   else
#       define MFUNC_OUT_DEC_STR        CONNECT2(   __MFUNC_OUT_DEC_DIGIT1,\
                                                    __MFUNC_OUT_DEC_DIGIT0)
#   endif
#else
#   define MFUNC_OUT_DEC_STR            CONNECT3(   __MFUNC_OUT_DEC_DIGIT2,\
                                                    __MFUNC_OUT_DEC_DIGIT1,\
                                                    __MFUNC_OUT_DEC_DIGIT0)
#endif


#undef MFUNC_IN_U8_DEC_VALUE


/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/

#ifdef __cplusplus
}
#endif
