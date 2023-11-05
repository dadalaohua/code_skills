#ifndef _LOG_h_
#define _LOG_h_
#include <stdio.h>
#define COL(x)  "\033[;" #x "m"
#define RED     COL(31)
#define GREEN   COL(32)
#define YELLOW  COL(33)
#define BLUE    COL(34)
#define MAGENTA COL(35)
#define CYAN    COL(36)
#define WHITE   COL(0)
#define GRAY    "\033[0m"
#define errlog(fmt, arg...) do{     \
    printf(RED"[#ERROR: Toeny Sun:"GRAY YELLOW" %s:%d]:"GRAY WHITE fmt GRAY, __func__, __LINE__, ##arg);\
}while(0)
#define log(fmt, arg...) do{     \
    printf(WHITE"[#DEBUG: Toeny Sun: "GRAY YELLOW"%s:%d]:"GRAY WHITE fmt GRAY, __func__, __LINE__, ##arg);\
}while(0)
#endif