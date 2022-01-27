/*
 * MIT License
 *
 * Copyright (c) 2019 极简美 @ konishi5202@163.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _EFSM_EVENT_H__
#define _EFSM_EVENT_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "efsm_conf.h"

/* Define your event here */
/* First way: use '#define' to define events, just like: */
// #define EVENT_PLAY    EFSM_EVENT(1)
// #define EVENT_STOP    EFSM_EVENT(2)
// #define EVENT_NEXT    EFSM_EVENT(3)
// #define EVENT_PREV    EFSM_EVENT(4)
// #define EVENT_START   EFSM_EVENT(7)   //not require continuous

/* Second way: use enum struct define events(recommend), just like: */
// enum {
// 	EVENT_PLAY  = EFSM_EVENT(1),
// 	EVENT_STOP  = EFSM_EVENT(2),
// 	EVENT_NEXT  = EFSM_EVENT(3),
// 	EVENT_PREV  = EFSM_EVENT(4),
// 	EVENT_START = EFSM_EVENT(7),    //not require continuous
// };

#define EVENT_PLAY    EFSM_EVENT(1)
#define EVENT_STOP    EFSM_EVENT(2)
#define EVENT_NEXT    EFSM_EVENT(3)
#define EVENT_PREV    EFSM_EVENT(4)
#define EVENT_START   EFSM_EVENT(7)   //not require continuous


#ifdef __cplusplus
}
#endif

#endif //_EFSM_EVENT_H__

