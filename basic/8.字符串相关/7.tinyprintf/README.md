# A tiny printf for embedded applications

[GitHub - cjlano/tinyprintf: A tiny printf and sprintf library for small embedded systems](https://github.com/cjlano/tinyprintf)

[About Spare Time Labs](http://www.sparetimelabs.com/tinyprintf/tinyprintf.php)

# A tiny [printf](http://en.wikipedia.org/wiki/Printf) for embedded applications

Effective as of 8th February 2021 this library can be licensed either under MIT, BSD or LGPL license.

自2021年2月8日起生效，此库可以根据MIT、BSD或LGPL许可证获得许可。

In my career of +25 years in embedded system programming I've found printing one of the most usefull debugging and trouble shooting tools. I won't go into my customary In Circuit Emulator (ICE) rant here, but I have to say that the other one is a single bit output with a LED and oscilloscope attached.

在我从事嵌入式系统编程超过25年的职业生涯中，我发现打印是最有用的调试和故障排除工具之一。我不会在这里讨论我习惯的在线仿真器（ICE），但我不得不说，另一个是连接了LED和示波器的单比特输出。

Some years ago I was bringing up a hobby board with a H8S processor when I needed to 'printf' something. My first thought was to hack something from the GNU standard C library, but that seemed like a lot of study/work and besides I was pretty convicended that in the end it would not fit easily into the memory available. So I searched the web for a light weight version, but could not find one. Amazing. Anyway I ended up spending an hour to write a tiny general purpose printf function which I'm sharing here.

几年前，当我需要“打印”一些东西时，我带了一个带有H8S处理器的开发板。我的第一个想法是从GNU标准C库中破解一些东西，但这似乎需要大量的学习/工作，而且我很确信，最终它将不容易适应可用的内存。所以我在网上搜索了一个轻量级的版本，但是没有找到。很神奇的。总之，我最后花了一个小时写了一个小的通用printf函数，我在这里分享一下。

The 'library' consists of two files listed below which you can also [download here.](http://www.sparetimelabs.com/tinyprintf/mit-bsd-lgpl-printf.zip)

“库”由下面列出的两个文件组成，你也可以[在这里下载](http://www.sparetimelabs.com/tinyprintf/mit-bsd-lgpl-printf.zip)。

The library is only some 200 lines long and has a memory footprint (on a 16/32 bit H8S) of about 1.4 kb. So you can propably use it in an 8 bit microcontroller with just some kilobytes of memory. And at 9600 bauds this code downloads in under two seconds, which is nice when debugging as my attention span seems to be rather short nowdays.

该库只有大约200行长，内存占用(在16/32位H8S上)约为1.4 kb。所以你可以在一个只有几千字节内存的8位微控制器中使用它。在9600波特的速度下，这段代码的下载时间不到两秒钟，这在调试的时候是很好的，因为现在我的注意力似乎很短。

To use it, just download the two files and include them in the make process of your project. In your source code and use the printf as you would use the one. Of course being tiny, it has limitations, no floating point support and long support is optional, but the most usefull features in embedded development, printing chars, strings, decimal and hex, are supported. `#include "printf.h"``stdio.h`

要使用它，只需下载这两个文件并将它们包含在项目的make过程中。在源代码中使用printf，就像使用一个一样。当然，由于它很小，它有一定的局限性，不支持浮点数，长支持是可选的，但它支持嵌入式开发中最有用的功能，打印字符、字符串、十进制和十六进制。”# include“printf.h”“stdio . h”

Before you can use the `printf` you need to initialize the library by supplying it with a character output function. Typically `printf` calls `putc` function but I chose not to do it that way. As the idea is that the code is as much as possible independent of anything else I did not want to presume the existence of any header files nor did I want to just declare the `putc` function with `extern` and trust the library user to provide it and linker to find it. Instead you need to pass a pointer to your `putc` function yourself. See the header file for an example and the code for details.

在使用`printf`之前，你需要通过提供字符输出函数来初始化库。通常`printf`调用`putc` 函数，但我选择不这样做。因为这个想法是代码尽可能独立于其他任何东西，我不想假设任何头文件的存在，也不想只是用`extern`声明`putc` 函数并信任库用户提供它和链接器来找到它。相反，你需要自己传递一个指针给你的`putc` 函数。请参阅头文件中的示例和代码以了解详细信息。

The library actually implements functions `tfp_printf` and `tfp_sprintf` and declared two macros, `printf` and `sprintf`, that expand to the names of the library functions. Now, I know, this sort of non function style macro usage, especially with lower case names, can be evil. A better/cleaner solution would have been the use of [variadic ](http://en.wikipedia.org/wiki/Variadic_macro)macros but for reasons lost in the dusk of history I did not. Feel free to modify either the macros or the function names.

该库实际上实现了函数`tfp_printf`和`tfp_sprintf`，并声明了两个宏`printf` 和 `sprintf`，它们展开为库函数的名称。现在，我知道，这种非函数风格的宏使用，特别是使用小写的名字，可能是邪恶的。一个更好/更干净的解决方案是使用可变参数宏([variadic](http://en.wikipedia.org/wiki/Variadic_macro) macros)，但由于历史的衰落，我没有这么做。可以随意修改宏或函数名。

To conserve space the library does not support printing `long int`s unless you define the macro `PRINTF_LONG_SUPPORT`. To support `long` the compiler will pull the 32 bit math libraries (assuming long is 32 bits here) and this will greatly increase the memory footprint. When debugging, especially when bringing up a board, space can be at premium, yet, if you are working with a 16/32 bit processor you may need to print 32 bit hex values. You can do that, without enablind the long support as follows:

为了节省空间，库不支持打印`long int`，除非你定义宏'`PRINTF_LONG_SUPPORT`。为了支持`long`，编译器将提取32位数学库(假设这里的long是32位)，这将大大增加内存占用。在调试时，特别是在启动电路板时，空间可能非常宝贵，但是，如果您使用的是16/32位处理器，则可能需要打印32位十六进制值。你可以这样做，不启用长支持，如下所示:

```c
long v=0xDEADBEEF;
printf("v=%04X%04X\n", v >> 16, v & 0xffff); // actually the '& 0xffff' is propably superfluous if int is 16 bits
```

This should output:`v=DEADBEEF `

这应该输出:`v=DEADBEEF`

Well, thats about all, just wanted to put this into the web so that if you need something like his you do not need to write it from scratch like I had to.

好吧，这就是所有，只是想把这个放到网上，所以如果你需要像他的东西，你不需要从头开始写，就像我不得不。



cheers Kusti / 17.5.2007

PS

An astute reader may have noticed that my `printf` is not 100% compliant with the standard: the return type is `void` instead of `int`. This is in keeping with the purpose of this 'library' -- to keep it lean and mean. For the life of me I cannot recall ever using the return value of printf for anything, so I felt that it was not worth the extra memory usage to include that feature.

精明的读者可能已经注意到我的`printf`并不是100%符合标准:返回类型是`void`而不是`int`。这符合这个“库”的宗旨——保持精简和吝啬。就我的一生而言，我不记得曾经使用过 printf 的返回值，所以我觉得不值得使用额外的内存来包含该特性。

This is the header file:

这是头文件:

```c
/*
File: printf.h

Copyright (C) 2004  Kustaa Nyholm

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

This library is realy just two files: 'printf.h' and 'printf.c'.

They provide a simple and small (+200 loc) printf functionality to 
be used in embedded systems.

I've found them so usefull in debugging that I do not bother with a 
debugger at all.

They are distributed in source form, so to use them, just compile them 
into your project. 

Two printf variants are provided: printf and sprintf. 

The formats supported by this implementation are: 'd' 'u' 'c' 's' 'x' 'X'.

Zero padding and field width are also supported.

If the library is compiled with 'PRINTF_SUPPORT_LONG' defined then the 
long specifier is also
supported. Note that this will pull in some long math routines (pun intended!)
and thus make your executable noticably longer.

The memory foot print of course depends on the target cpu, compiler and 
compiler options, but a rough guestimate (based on a H8S target) is about 
1.4 kB for code and some twenty 'int's and 'char's, say 60 bytes of stack space. 
Not too bad. Your milage may vary. By hacking the source code you can 
get rid of some hunred bytes, I'm sure, but personally I feel the balance of 
functionality and flexibility versus  code size is close to optimal for
many embedded systems.

To use the printf you need to supply your own character output function, 
something like :

	void putc ( void* p, char c)
		{
		while (!SERIAL_PORT_EMPTY) ;
		SERIAL_PORT_TX_REGISTER = c;
		}

Before you can call printf you need to initialize it to use your 
character output function with something like:

	init_printf(NULL,putc);

Notice the 'NULL' in 'init_printf' and the parameter 'void* p' in 'putc', 
the NULL (or any pointer) you pass into the 'init_printf' will eventually be 
passed to your 'putc' routine. This allows you to pass some storage space (or 
anything realy) to the character output function, if necessary. 
This is not often needed but it was implemented like that because it made 
implementing the sprintf function so neat (look at the source code).

The code is re-entrant, except for the 'init_printf' function, so it 
is safe to call it from interupts too, although this may result in mixed output. 
If you rely on re-entrancy, take care that your 'putc' function is re-entrant!

The printf and sprintf functions are actually macros that translate to 
'tfp_printf' and 'tfp_sprintf'. This makes it possible
to use them along with 'stdio.h' printf's in a single source file. 
You just need to undef the names before you include the 'stdio.h'.
Note that these are not function like macros, so if you have variables
or struct members with these names, things will explode in your face.
Without variadic macros this is the best we can do to wrap these
fucnction. If it is a problem just give up the macros and use the
functions directly or rename them.

For further details see source code.

regs Kusti, 23.10.2004
*/


#ifndef __TFP_PRINTF__
#define __TFP_PRINTF__

#include <stdarg.h>

void init_printf(void* putp,void (*putf) (void*,char));

void tfp_printf(char *fmt, ...);
void tfp_sprintf(char* s,char *fmt, ...);

void tfp_format(void* putp,void (*putf) (void*,char),char *fmt, va_list va);

#define printf tfp_printf 
#define sprintf tfp_sprintf 

#endif
```

And here is the actual source code file:

这里是实际的源代码文件:

```c
/*
File: printf.c

Copyright (C) 2004  Kustaa Nyholm

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "printf.h"

typedef void (*putcf) (void*,char);
static putcf stdout_putf;
static void* stdout_putp;


#ifdef PRINTF_LONG_SUPPORT

static void uli2a(unsigned long int num, unsigned int base, int uc,char * bf)
    {
    int n=0;
    unsigned int d=1;
    while (num/d >= base)
        d*=base;         
    while (d!=0) {
        int dgt = num / d;
        num%=d;
        d/=base;
        if (n || dgt>0|| d==0) {
            *bf++ = dgt+(dgt<10 ? '0' : (uc ? 'A' : 'a')-10);
            ++n;
            }
        }
    *bf=0;
    }

static void li2a (long num, char * bf)
    {
    if (num<0) {
        num=-num;
        *bf++ = '-';
        }
    uli2a(num,10,0,bf);
    }

#endif

static void ui2a(unsigned int num, unsigned int base, int uc,char * bf)
    {
    int n=0;
    unsigned int d=1;
    while (num/d >= base)
        d*=base;        
    while (d!=0) {
        int dgt = num / d;
        num%= d;
        d/=base;
        if (n || dgt>0 || d==0) {
            *bf++ = dgt+(dgt<10 ? '0' : (uc ? 'A' : 'a')-10);
            ++n;
            }
        }
    *bf=0;
    }

static void i2a (int num, char * bf)
    {
    if (num<0) {
        num=-num;
        *bf++ = '-';
        }
    ui2a(num,10,0,bf);
    }

static int a2d(char ch)
    {
    if (ch>='0' && ch<='9') 
        return ch-'0';
    else if (ch>='a' && ch<='f')
        return ch-'a'+10;
    else if (ch>='A' && ch<='F')
        return ch-'A'+10;
    else return -1;
    }

static char a2i(char ch, char** src,int base,int* nump)
    {
    char* p= *src;
    int num=0;
    int digit;
    while ((digit=a2d(ch))>=0) {
        if (digit>base) break;
        num=num*base+digit;
        ch=*p++;
        }
    *src=p;
    *nump=num;
    return ch;
    }

static void putchw(void* putp,putcf putf,int n, char z, char* bf)
    {
    char fc=z? '0' : ' ';
    char ch;
    char* p=bf;
    while (*p++ && n > 0)
        n--;
    while (n-- > 0) 
        putf(putp,fc);
    while ((ch= *bf++))
        putf(putp,ch);
    }

void tfp_format(void* putp,putcf putf,char *fmt, va_list va)
    {
    char bf[12];
    
    char ch;


    while ((ch=*(fmt++))) {
        if (ch!='%') 
            putf(putp,ch);
        else {
            char lz=0;
#ifdef  PRINTF_LONG_SUPPORT
            char lng=0;
#endif
            int w=0;
            ch=*(fmt++);
            if (ch=='0') {
                ch=*(fmt++);
                lz=1;
                }
            if (ch>='0' && ch<='9') {
                ch=a2i(ch,&fmt,10,&w);
                }
#ifdef  PRINTF_LONG_SUPPORT
            if (ch=='l') {
                ch=*(fmt++);
                lng=1;
            }
#endif
            switch (ch) {
                case 0: 
                    goto abort;
                case 'u' : {
#ifdef  PRINTF_LONG_SUPPORT
                    if (lng)
                        uli2a(va_arg(va, unsigned long int),10,0,bf);
                    else
#endif
                    ui2a(va_arg(va, unsigned int),10,0,bf);
                    putchw(putp,putf,w,lz,bf);
                    break;
                    }
                case 'd' :  {
#ifdef  PRINTF_LONG_SUPPORT
                    if (lng)
                        li2a(va_arg(va, unsigned long int),bf);
                    else
#endif
                    i2a(va_arg(va, int),bf);
                    putchw(putp,putf,w,lz,bf);
                    break;
                    }
                case 'x': case 'X' : 
#ifdef  PRINTF_LONG_SUPPORT
                    if (lng)
                        uli2a(va_arg(va, unsigned long int),16,(ch=='X'),bf);
                    else
#endif
                    ui2a(va_arg(va, unsigned int),16,(ch=='X'),bf);
                    putchw(putp,putf,w,lz,bf);
                    break;
                case 'c' : 
                    putf(putp,(char)(va_arg(va, int)));
                    break;
                case 's' : 
                    putchw(putp,putf,w,0,va_arg(va, char*));
                    break;
                case '%' :
                    putf(putp,ch);
                default:
                    break;
                }
            }
        }
    abort:;
    }


void init_printf(void* putp,void (*putf) (void*,char))
    {
    stdout_putf=putf;
    stdout_putp=putp;
    }

void tfp_printf(char *fmt, ...)
    {
    va_list va;
    va_start(va,fmt);
    tfp_format(stdout_putp,stdout_putf,fmt,va);
    va_end(va);
    }

static void putcp(void* p,char c)
    {
    *(*((char**)p))++ = c;
    }



void tfp_sprintf(char* s,char *fmt, ...)
    {
    va_list va;
    va_start(va,fmt);
    tfp_format(&s,putcp,fmt,va);
    putcp(&s,0);
    va_end(va);
    }
```

