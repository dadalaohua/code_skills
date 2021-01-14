//==========================================================================
//
//      crc.h
//
//      Interface for the CRC algorithms.
//==========================================================================
 
#ifndef __CRC32_H__
#define __CRC32_H__
 
// Gary S. Brown's 32 bit CRC
 
unsigned int cyg_crc32(unsigned char *s, int len);
 
// Gary S. Brown's 32 bit CRC, but accumulate the result from a
// previous CRC calculation
 
unsigned int cyg_crc32_accumulate(unsigned int crc, unsigned char *s, int len);
 
// Ethernet FCS Algorithm
 
unsigned int cyg_ether_crc32(unsigned char *s, int len);
 
// Ethernet FCS algorithm, but accumulate the result from a previous
// CRC calculation.
 
unsigned int cyg_ether_crc32_accumulate(unsigned int crc, unsigned char *s,
        int len);
 
/**
 * add 4 bytes num[4] to change crc32 value from crc_src to crc_dst
 * @return: 0 on success, -1 on error.
 */
int cyg_crc32_change(unsigned int crc_dst, unsigned int crc_src, unsigned char num[4]);
 
/**
 * cyg_crc32_reserve - reserve CRC32 value by dropping data[len]
 * @return: return the CRC value before data[len]
 */
unsigned int cyg_crc32_reserve(unsigned int crc, void *data, int len);
 
#endif // __CRC32_H__
