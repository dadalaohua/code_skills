#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "encrypt.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    Huge               rsatmp,
                       rsaptx,
                       rsactx;

    RsaPubKey          rsapubkey;
    RsaPriKey          rsaprikey;

    int                i;

    //Encipher some data using RSA.
    fprintf(stdout, "Enciphering with RSA\n");

    rsapubkey.e = 17;
    rsapubkey.n = 209;
    rsaprikey.d = 53;
    rsaprikey.n = 209;

    fprintf(stdout, "d=%lu, e=%lu, n=%lu\n", rsaprikey.d, rsapubkey.e, rsapubkey.n);

    for (i = 0; i < 128; i++) {

       rsatmp = i;
       rsa_encipher(rsatmp, &rsactx, rsapubkey);
       rsa_decipher(rsactx, &rsaptx, rsaprikey);

       if (rsatmp == rsaptx)
          fprintf(stdout, "rsatmp=%5lu, rsactx=%5lu, rsaptx=%5lu (OK)\n", rsatmp,
             rsactx, rsaptx);
       else
          fprintf(stdout, "rsatmp=%5lu, rsactx=%5lu, rsaptx=%5lu (ERROR)\n", rsatmp,
             rsactx, rsaptx);

    }

    return 0;
}