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

#include <stdio.h>
#include <stdlib.h>

#include "efsm.h"
#include "efsm_event.h"
#include "startup_function.h"

/* 1. define you own state name */
EFSM_CREATE(startup);

/* 2. define a sets of event-handler */
static EFSM_SETS startup[] = { {EVENT_PLAY, media_control},
                               {EVENT_STOP, media_control},
                               {EVENT_NEXT, media_control},
                               {EVENT_PREV, media_control},
                               {EVENT_START, media_control},
                             };


void startup_init(void)
{	
	/* 3. bind your state to sets */
	EFSM_BIND(startup, startup);	
}

