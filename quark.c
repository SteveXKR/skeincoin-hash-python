#include "quark.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include <openssl/sha.h>

#include "sha3/sph_skein.h"

void quark_hash(const char* input, char* output)
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
