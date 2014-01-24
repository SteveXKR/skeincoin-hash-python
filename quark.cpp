#include "quark.h"
#include "uint256.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include <openssl/sha.h>

#include "sha3/sph_skein.h"

uint256 quark_hash(const T1 pbegin, const T1 pend)
{

    sph_skein512_context ctx_skein;
    static unsigned char pblank[1];

    uint512 hash1;
    uint256 hash2;

    sph_skein512_init(&ctx_skein);
    sph_skein512(&ctx_skein, (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0])), (pend - pbegin) * sizeof(pbegin[0]));
    sph_skein512_close(&ctx_skein, static_cast<void*>(&hash1));
    
    SHA256((unsigned char*)&hash1, 64, (unsigned char*)&hash2);
    
    return hash2;


}


