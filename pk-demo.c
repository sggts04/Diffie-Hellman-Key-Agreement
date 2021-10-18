/*
 *
 *   1024 bit Diffie-Hellman Key Exchange
 *
 */

#include <stdio.h>
#include "miracl.h"
#include <time.h>

/* large 1024 bit prime p for which (p-1)/2 is also prime */
char *primetext=
"155315526351482395991155996351231807220169644828378937433223838972232518351958838087073321845624756550146945246003790108045940383194773439496051917019892370102341378990113959561895891019716873290512815434724157588460613638202017020672756091067223336194394910765309830876066246480156617492164140095427773547319";


int main() {
    time_t seed;
    big a,b,p,pa,pb,key;
    miracl *mip;
#ifndef MR_NOFULLWIDTH   
    mip=mirsys(36,0);
#else
    mip=mirsys(36,MAXBASE);
#endif
    a=mirvar(0);
    b=mirvar(0);
    p=mirvar(0);
    pa=mirvar(0);
    pb=mirvar(0);
    key=mirvar(0);


    time(&seed);
    irand((unsigned long)seed);   /* change parameter for different values */

    printf("First Diffie-Hellman Key exchange .... \n");

    cinstr(p,primetext);

    printf("\nAlice's offline calculation\n");        
    bigbits(160,a);

/* 3 generates the sub-group of prime order (p-1)/2 */

    powltr(3,a,p,pa);

    printf("Bob's offline calculation\n");        
    bigbits(160,b);
    powltr(3,b,p,pb);

    printf("Alice calculates Key=\n");
    powmod(pb,a,p,key);
    cotnum(key,stdout);

    printf("Bob calculates Key=\n");
    powmod(pa,b,p,key);
    cotnum(key,stdout);

    printf("Alice and Bob's keys should be the same!\n");


    return 0;
}

