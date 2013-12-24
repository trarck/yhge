#include "RandomMT.h"

NS_CC_YHGE_BEGIN

unsigned long RandomMT::mag01[2]= { 0x0, MATRIX_A };

//static const unsigned long DEFAULT_SEED= 4357;


void RandomMT::initSeed(unsigned long seed)
{
    /* setting initial seeds to mt[N] using         */
    /* the generator Line 25 of Table 1 in          */
    /* [KNUTH 1981, The Art of Computer Programming */
    /*    Vol. 2 (2nd Ed.), pp102]                  */
    mt[0] = seed & 0xffffffffU;
    for (mti = 1; mti < N; ++mti)
    {
        mt[mti] = (69069 * mt[mti - 1]) & 0xffffffffU;
    }
}

unsigned long RandomMT::GenerateUInt()
{
    unsigned long y;
    
    /* mag01[x] = x * MATRIX_A  for x=0,1 */
    if (mti >= N) /* generate N words at one time */
    {
        short kk = 0;
        
        for (; kk < N - M; ++kk)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        
        for(;kk < N - 1; ++kk)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk+(M - N)] ^ (y >> 1) ^ mag01[y & 0x1];
        }
        
        y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1];
        
        mti = 0;
    }
    
    y = mt[mti++];
    y ^= (y >> 11);
    y ^= (y <<  7) & TEMPERING_MASK_B;
    y ^= (y << 15) & TEMPERING_MASK_C;
    y ^= (y >> 18);
    
    return y;
}

NS_CC_YHGE_END