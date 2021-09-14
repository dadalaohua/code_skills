/*
 * The MIT License (MIT)
 *
 * Copyright © 2015-2016 Franklin "Snaipe" Mathieu <http://snai.pe/>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef CSPTR_COMMON_H_
# define CSPTR_COMMON_H_

# ifdef __GNUC__
#  define CSPTR_INLINE      __attribute__ ((always_inline)) inline
#  define CSPTR_MALLOC_API  __attribute__ ((malloc))
#  define CSPTR_PURE        __attribute__ ((pure))
# elif defined(_MSC_VER)
#  define CSPTR_INLINE      __forceinline
#  define CSPTR_MALLOC_API
#  define CSPTR_PURE
# else
#  define CSPTR_INLINE
#  define CSPTR_MALLOC_API
#  define CSPTR_PURE
# endif

#endif /* !CSPTR_COMMON_H_ */
