/*****************************************************************************
*                                                                            *
*  ------------------------------- encrypt.h ------------------------------  *
*                                                                            *
*****************************************************************************/

#ifndef ENCRYPT_H
#define ENCRYPT_H

/*****************************************************************************
*                                                                            *
*  --------------------------- Public Interface ---------------------------  *
*                                                                            *
*****************************************************************************/

void des_encipher(const unsigned char *plaintext, unsigned char *ciphertext,
   const unsigned char *key);

void des_decipher(const unsigned char *ciphertext, unsigned char *plaintext,
   const unsigned char *key);

#endif
