/* Takuji Nishimura, considering the suggestions by            */
/* Topher Cooper and Marc Rieffel in July-Aug. 1997.           */
/* This library is free software under the Artistic license:   */
/*                                                             */
/* You can find the original C-program at                      */
/*     http://www.math.keio.ac.jp/~matumoto/mt.html            */
/*                                                             */

#ifndef YHGE_MATH_RANDOMMT_H_
#define YHGE_MATH_RANDOMMT_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

#define MT_MAX_UINT 0xffffffff
#define MT_MAX_INT 0x7fffffff
#define MT_DEFAULT_SEED 4357

NS_CC_YHGE_BEGIN

class RandomMT
{
    
public:
    
    /* initializing the array with a NONZERO seed */
  
    inline RandomMT()
    :mti(N+1)
    {
        /* a default initial seed is used   */
        initSeed(MT_DEFAULT_SEED);
    }
    
    inline RandomMT(unsigned long seed)
    :mti(N+1)
    {
        initSeed(seed);
    }
    
    void initSeed(unsigned long seed);
    
    /* generates a random number on [0,0xffffffff]-interval */
    inline unsigned long NextUInt()
    {
        return GenerateUInt();
    }

    //[0,max]
    inline unsigned long NextUInt(unsigned long max)
    {
        return (unsigned long)(GenerateUInt() / ((double)MT_MAX_UINT / max));
    }

    //[min,max]
    inline unsigned long NextUInt(unsigned long min, unsigned long max) /* throws ArgumentOutOfRangeException */
    {
        if (min >= max)
        {
            return max==min?min:0;
        }

        return (unsigned long)(GenerateUInt() / ((double)MT_MAX_UINT / (max - min)) + min);
    }

    //[0,0x7fffffff)
    
    inline int Next()
    {
        return Next(MT_MAX_INT);
    }
    
    //[0,max)
    inline int Next(int max) /* throws ArgumentOutOfRangeException */
    {
        if (max <= 1)
        {
            if (max < 0)
            {
                throw "ArgumentOutOfRangeException";
            }

            return 0;
        }

        return (int)(NextDouble() * max);
    }
    
    //[min,max)
    inline int Next(int min, int max)
    {
        if (max < min)
        {
            throw "ArgumentOutOfRangeException";
        }
        else if(max == min)
        {
            return min;
        }
        else
        {
            return Next(max - min) + min;
        }
    }

    
    //[0,1)
    inline double NextDouble()
    {
        return (double)GenerateUInt() / ((unsigned long long)MT_MAX_UINT + 1);
    }

protected:
    /* generates a random number on [0,0xffffffff]-interval */
    unsigned long GenerateUInt();
    
private:

    /* Period parameters */
    static const int N = 624;
    static const int M = 397;
    static const unsigned long MATRIX_A   = 0x9908b0df; /* constant vector a */
    static const unsigned long UPPER_MASK = 0x80000000; /* most significant w-r bits */
    static const unsigned long LOWER_MASK = 0x7fffffff; /* least significant r bits */
    
    /* Tempering parameters */
    static const unsigned long TEMPERING_MASK_B = 0x9d2c5680;
    static const unsigned long TEMPERING_MASK_C = 0xefc60000;
    
//    static const unsigned long DEFAULT_SEED;
    
    static unsigned long mag01[2] ;
    
    unsigned long mt[N]; /* the array for the state vector  */
    
    short mti;
    
};

NS_CC_YHGE_END

#endif // YHGE_MATH_RANDOMMT_H_