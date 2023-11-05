#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include "minIni.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    const char inifile[] = "test.ini";
    char str[100];
    long n;
    
    n = ini_puts("middle", "ip_addr", "192.168.31.50", inifile);
    assert(n==1);
    
    n = ini_puts("middle", "ip_port", "8080", inifile);
    assert(n==1);
    
    n = ini_puts("middle", "dev_addr", "0x01", inifile);
    assert(n==1);
    
    n = ini_puts("slave", "sampling_freq", "100", inifile);
    assert(n==1);
    
    n = ini_puts("slave0", "channel", "0x0f", inifile);
    assert(n==1);
    
    n = ini_puts("slave1", "channel", "0x0f", inifile);
    assert(n==1);
    
    n = ini_puts("slave2", "channel", "0x0f", inifile);
    assert(n==1);
    
    ini_gets("middle", "ip_addr", "dummy", str, sizearray(str), inifile);
    printf("str %s %s %s\n", "middle", "ip_addr", str);
    
    ini_gets("middle", "ip_port", "dummy", str, sizearray(str), inifile);
    printf("str %s %s %s\n", "middle", "ip_port", str);
    
    ini_gets("middle", "dev_addr", "dummy", str, sizearray(str), inifile);
    printf("str %s %s %s\n", "middle", "dev_addr", str);
    
    ini_gets("slave", "sampling_freq", "dummy", str, sizearray(str), inifile);
    printf("str %s %s %s\n", "slave", "sampling_freq", str);
    
    ini_gets("slave0", "channel", "dummy", str, sizearray(str), inifile);
    printf("str %s %s %s\n", "slave0", "channel", str);
    
    ini_gets("slave1", "channel", "dummy", str, sizearray(str), inifile);
    printf("str %s %s %s\n", "slave1", "channel", str);
    
    ini_gets("slave2", "channel", "dummy", str, sizearray(str), inifile);
    printf("str %s %s %s\n", "slave1", "channel", str);
    
    ini_gets("slave3", "channel", "dummy", str, sizearray(str), inifile);
    printf("str %s %s %s\n", "slave1", "channel", str);

    return 0;
}