/*
 A C-program for MT19937, with initialization improved 2002/1/26.
 Coded by Takuji Nishimura and Makoto Matsumoto.
 
 Before using, initialize the state by using initGenrand(seed)
 or initByArray(init_key, key_length).
 
 Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:
 
 1. Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 
 3. The names of its contributors may not be used to endorse or promote
 products derived from this software without specific prior written
 permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 
 Any feedback is very welcome.
 http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
 email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
 */

#ifndef YHGE_MATH_MERSENNETWISTER_H_
#define YHGE_MATH_MERSENNETWISTER_H_

#include <yhge/YHGEMacros.h>

#define Mersenne_Twister_N 624
#define Mersenne_Twister_M 397
#define Mersenne_Twister_MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define Mersenne_Twister_UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define Mersenne_Twister_LOWER_MASK 0x7fffffffUL /* least significant r bits */

NS_CC_YHGE_BEGIN

class MersenneTwister
{
public:
    
    inline MersenneTwister()
    :mti(Mersenne_Twister_N+1)
    {
        
    }
    inline MersenneTwister(unsigned long seed)
    :mti(Mersenne_Twister_N+1)
    {
        initGenrand(seed);
    }
    
    /* initializes mt[Mersenne_Twister_N] with a seed */
    void initGenrand(unsigned long s);
    
    /* initialize by an array with array-length */
    /* init_key is the array for initializing keys */
    /* key_length is its length */
    /* slight change for C++, 2004/2/26 */
    void initByArray(unsigned long init_key[], int key_length);
    
    /* generates a random number on [0,0xffffffff]-interval */
    unsigned long genrandInt32(void);
    
    /* generates a random number on [0,0x7fffffff]-interval */
    inline long genrandInt31(void)
    {
        return (long)(genrandInt32()>>1);
    }
    
    /* generates a random number on [0,1]-real-interval */
    inline double genrandReal1(void)
    {
        return genrandInt32()*(1.0/4294967295.0);
        /* divided by 2^32-1 */
    }
    
    /* generates a random number on [0,1)-real-interval */
    inline double genrandReal2(void)
    {
        return genrandInt32()*(1.0/4294967296.0);
        /* divided by 2^32 */
    }
    
    /* generates a random number on (0,1)-real-interval */
    inline double genrandReal3(void)
    {
        return (((double)genrandInt32()) + 0.5)*(1.0/4294967296.0); 
        /* divided by 2^32 */
    }
    
    /* generates a random number on [0,1) with 53-bit resolution*/
    inline double genrandRes53(void)
    { 
        unsigned long a=genrandInt32()>>5, b=genrandInt32()>>6; 
        return(a*67108864.0+b)*(1.0/9007199254740992.0); 
    } 
    /* These real versions are due to Isaku Wada, 2002/01/09 added */
    

private:
    unsigned long mt[Mersenne_Twister_N]; /* the array for the state vector  */
    
    int mti;//=Mersenne_Twister_N+1; /* mti==Mersenne_Twister_N+1 means mt[Mersenne_Twister_N] is not initialized */
    
};

NS_CC_YHGE_END

#endif // YHGE_MATH_MERSENNETWISTER_H_
