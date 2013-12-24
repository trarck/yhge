#include "MersenneTwister.h"

NS_CC_YHGE_BEGIN

/* initializes mt[Mersenne_Twister_N] with a seed */
void MersenneTwister::initGenrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<Mersenne_Twister_N; mti++) {
        mt[mti] =
        (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void MersenneTwister::initByArray(unsigned long init_key[], int key_length)
{
    int i, j, k;
    initGenrand(19650218UL);
    i=1; j=0;
    k = (Mersenne_Twister_N>key_length ? Mersenne_Twister_N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
        + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=Mersenne_Twister_N) { mt[0] = mt[Mersenne_Twister_N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=Mersenne_Twister_N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
        - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=Mersenne_Twister_N) { mt[0] = mt[Mersenne_Twister_N-1]; i=1; }
    }
    
    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long MersenneTwister::genrandInt32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, Mersenne_Twister_MATRIX_A};
    /* mag01[x] = x * Mersenne_Twister_MATRIX_A  for x=0,1 */
    
    if (mti >= Mersenne_Twister_N) { /* generate Mersenne_Twister_N words at one time */
        int kk;
        
        if (mti == Mersenne_Twister_N+1)   /* if initGenrand() has not been called, */
            initGenrand(5489UL); /* a default initial seed is used */
        
        for (kk=0;kk<Mersenne_Twister_N-Mersenne_Twister_M;kk++) {
            y = (mt[kk]&Mersenne_Twister_UPPER_MASK)|(mt[kk+1]&Mersenne_Twister_LOWER_MASK);
            mt[kk] = mt[kk+Mersenne_Twister_M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<Mersenne_Twister_N-1;kk++) {
            y = (mt[kk]&Mersenne_Twister_UPPER_MASK)|(mt[kk+1]&Mersenne_Twister_LOWER_MASK);
            mt[kk] = mt[kk+(Mersenne_Twister_M-Mersenne_Twister_N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[Mersenne_Twister_N-1]&Mersenne_Twister_UPPER_MASK)|(mt[0]&Mersenne_Twister_LOWER_MASK);
        mt[Mersenne_Twister_N-1] = mt[Mersenne_Twister_M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];
        
        mti = 0;
    }
    
    y = mt[mti++];
    
    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);
    
    return y;
}

NS_CC_YHGE_END