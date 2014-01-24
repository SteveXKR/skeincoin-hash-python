#ifndef HASHBLOCK_H
#define HASHBLOCK_H

#include "sph_blake.h"
#include "sph_bmw.h"
#include "sph_groestl.h"
#include "sph_jh.h"
#include "sph_keccak.h"
#include "sph_skein.h"



void Hash9(void *state, const void *init)
{
    sph_skein512_context     ctx_skein;
    static unsigned char pblank[1];

	
    uint32_t mask = 8;
    uint32_t zero = 0;

	//these uint512 in the c++ source of the client are backed by an array of uint32
    uint32_t hashA[16], hashB[16];	
	
/*	
	int ii=0;
	printf("Start: ");
	for (ii=0; ii < 80; ii++)
	{
		printf ("%.2x",((uint8_t*)init)[ii]);
	};
	printf ("\n");
*/	
	
	 //0
	
/*	
	printf("bla512: ");
	for (ii=0; ii < 64; ii++)
	{
		printf ("%.2x",((uint8_t*)hashA)[ii]);
	};
	printf ("\n");
*/	
	
   //1

/*
	printf("bmw512: ");
	for (ii=0; ii < 64; ii++)
	{
		printf ("%.2x",((uint8_t*)hashB)[ii]);
	};
	printf ("\n");	
*/
	

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, hashA, 64); //6
    sph_skein512_close(&ctx_skein, hashB); //7



/*	
	printf("result: ");
	for (ii=0; ii < 64; ii++)
	{
		printf ("%.2x",((uint8_t*)hashA)[ii]);
	};
	printf ("\n");	
*/
    //return hash[8].trim256(); //8
	memcpy(state, hashA, 32);
	
/*	
	printf("result: ");
	for (ii=0; ii < 32; ii++)
	{
		printf ("%.2x",((uint8_t*)state)[ii]);
	};
	printf ("\n");	
*/	
}



void Hash6(void *state, const void *init)

{
    sph_skein512_context     ctx_skein;
    //static unsigned char pblank[1];

    char hashA[64], hashB[64];

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, (const void*)(hashA), 64);
    sph_skein512_close(&ctx_skein, (void*)(hashB));

    memcpy(state, hashB, 32);
};


#endif // HASHBLOCK_H
