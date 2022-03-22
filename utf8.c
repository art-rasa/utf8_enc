#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include "utf8.h"

static int get_num_bytes(unsigned int character);
static unsigned int get_bits(unsigned int char_reg, int begin, int end);

/* 
 * Encodes the given character's Unicode code point using UTF-8 coding.
 * Parameters:
 *      character   Unicode code point as an unsigned integer.
 *      utf8        Array for UTF-8 encoded bytes (can be 1..4 bytes).
 */
void utf8_encode(unsigned int character, unsigned char utf8[]) 
{
    int num_bytes = 0;
    const int utf8_len = 4+1;
    int i = 0;
    unsigned int tmp_bits = 0;
    
    num_bytes = get_num_bytes(character);
    
    for (i = 0; i < utf8_len; i++) 
    {
        utf8[i] = '\0';
    }
    
    switch (num_bytes) 
    {
    case 1:
        /* utf8[0]: 0xxx|xxxx -> 7 databits (0..127) */
        tmp_bits = get_bits(character, 0, 8);
        utf8[0] = (unsigned char)tmp_bits;
        break;
        
    case 2:
        /* utf8[0]: 110x|xxxx 
           utf8[1]: 10xx|xxxx -> 11 databits (128..2047) */
        tmp_bits = get_bits(character, 0, 6);
        utf8[1] = (unsigned char)tmp_bits;
        
        tmp_bits = get_bits(character, 6, 11);
        utf8[0] = (unsigned char)tmp_bits;
        
        utf8[0] |= (1 << 6) | (1 << 7);
        utf8[1] |= (1 << 7);
        break;
        
    case 3:
        /* utf8[0]: 1110|xxxx
           utf8[1]: 10xx|xxxx
           utf8[2]: 10xx|xxxx -> 16 databits (2048..65 535) */
        tmp_bits = get_bits(character, 0, 6);
        utf8[2] = (unsigned char)tmp_bits;
        
        tmp_bits = get_bits(character, 6, 12);
        utf8[1] = (unsigned char)tmp_bits;
        
        tmp_bits = get_bits(character, 12, 16);
        utf8[0] = (unsigned char)tmp_bits;
        
        utf8[0] |= (1 << 5) | (1 << 6) | (1 << 7);
        utf8[1] |= (1 << 7);
        utf8[2] |= (1 << 7);
        break;
        
    case 4:
        /* utf8[0]: 1111|0xxx
           utf8[1]: 10xx|xxxx
           utf8[2]: 10xx|xxxx
           utf8[3]: 10xx|xxxx -> 21 databits (65 536..2 097 151) */
        tmp_bits = get_bits(character, 0, 6);
        utf8[3] = (unsigned char)tmp_bits;
        
        tmp_bits = get_bits(character, 6, 12);
        utf8[2] = (unsigned char)tmp_bits;
        
        tmp_bits = get_bits(character, 12, 18);
        utf8[1] = (unsigned char)tmp_bits;
        
        tmp_bits = get_bits(character, 18, 21);
        utf8[0] = (unsigned char)tmp_bits;
        
        utf8[0] |= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
        utf8[1] |= (1 << 7);
        utf8[2] |= (1 << 7);
        utf8[3] |= (1 << 7);
        break;
        
    default:
        break;
    }
    
}


/* Prints a given number of bits from a 32-bit u-int variable. */
void print_bits(unsigned int bit_register, int num) 
{
    bool bit = false;
    int i = 0;
    
    for (i = 31; i >= 0; i--) 
    {
        bit = bit_register & (1 << i);
        
        if (i >= num) 
        {
            continue;
        }
        
        printf("%d", bit);
        
        if ((i % 8) == 0) 
        {
            printf(" ");
        }
    }
}


/* Returns the bits of an 32-bit unsigned int variable over a given 
 * position. Begin bit is included, but end bit is excluded. */
static unsigned int get_bits(unsigned int char_reg, int begin, int end)
{
    int i = 0;
    unsigned int bits = 0;
    
    for (i = begin; i < end; i++) 
    {
        if (char_reg & (1 << i)) 
        {
            bits |= (1 << (i - begin));
        } 
    }
    
    return bits;
}


/* Counts the number of 8-bit bytes that are required to encode a given
 * Unicode code point using UTF-8 coding. */
static int get_num_bytes(unsigned int character)
{
    int num_bytes = 0;
    int i = 0;
    int bit_pos = 0;
    const int num_bits = sizeof(unsigned int) * CHAR_BIT;
    
    for (i = 0; i < num_bits; i++) 
    {
        if (character & (1 << i)) 
        {
            bit_pos = i;
        }
    }
    
    /* Double-byte encoding (e.g. Scandinavian letters) */
    if ((bit_pos > 6) && (bit_pos <= 10)) 
    {
        num_bytes = 2;
    } 
    /* Triple-byte encoding (e.g. CJK characters) */
    else if ((bit_pos > 10) && (bit_pos <= 15)) 
    {
        num_bytes = 3;
    } 
    /* Quad-byte encoding (e.g. special characters) */
    else if (bit_pos > 15) 
    {
        num_bytes = 4;
    } 
    /* Single-byte encoding (ASCII characters) */
    else 
    {
        num_bytes = 1;
    }
    
    return num_bytes;
}

































