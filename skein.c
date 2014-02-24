#include "skein.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <openssl/sha.h>

#include "sha3/sph_skein.h"

static __inline uint32_t
be32dec(const void *pp)
{
        const uint8_t *p = (uint8_t const *)pp;

        return ((uint32_t)(p[3]) + ((uint32_t)(p[2]) << 8) +
            ((uint32_t)(p[1]) << 16) + ((uint32_t)(p[0]) << 24));
}

static __inline void
be32enc(void *pp, uint32_t x)
{
        uint8_t * p = (uint8_t *)pp;

        p[3] = x & 0xff;
        p[2] = (x >> 8) & 0xff;
        p[1] = (x >> 16) & 0xff;
        p[0] = (x >> 24) & 0xff;
}

static __inline uint32_t
le32dec(const void *pp)
{
        const uint8_t *p = (uint8_t const *)pp;

        return ((uint32_t)(p[0]) + ((uint32_t)(p[1]) << 8) +
            ((uint32_t)(p[2]) << 16) + ((uint32_t)(p[3]) << 24));
}

static __inline void
le32enc(void *pp, uint32_t x)
{
        uint8_t * p = (uint8_t *)pp;

        p[0] = x & 0xff;
        p[1] = (x >> 8) & 0xff;
        p[2] = (x >> 16) & 0xff;
        p[3] = (x >> 24) & 0xff;
}

/*
 * Encode a length len/4 vector of (uint32_t) into a length len vector of
 * (unsigned char) in big-endian form.  Assumes len is a multiple of 4.
 */
static void
be32enc_vect(unsigned char *dst, const uint32_t *src, size_t len)
{
        size_t i;

        for (i = 0; i < len / 4; i++)
                be32enc(dst + i * 4, src[i]);
}

/*
 * Decode a big-endian length len vector of (unsigned char) into a length
 * len/4 vector of (uint32_t).  Assumes len is a multiple of 4.
 */
static void
be32dec_vect(uint32_t *dst, const unsigned char *src, size_t len)
{
        size_t i;

        for (i = 0; i < len / 4; i++)
                dst[i] = be32dec(src + i * 4);
}
    

void skein_hash(const char* input, char* output)
{

    
    sph_skein512_context     ctx_skein;
    static unsigned char pblank[1];

    uint32_t mask = 8;
    uint32_t zero = 0;

        //these uint512 in the c++ source of the client are backed by an array of uint32
    uint32_t hashA[16], hashB[16];        
        
    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, input, 80); //6
    sph_skein512_close(&ctx_skein, hashA); //7

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, hashA, 64);
    SHA256_Final(hashB, &sha256);

    memcpy(output, hashB, 32);
        

/*        int ii;
        printf("result: ");
        for (ii=0; ii < 32; ii++)
        {
                printf ("%.2x",((uint8_t*)state)[ii]);
        };
        printf ("\n");        
*/        
}
