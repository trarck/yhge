#ifndef YHGE_MATH_FLOATUTIL_H_
#define YHGE_MATH_FLOATUTIL_H_

#include <math.h>
#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

#define YHGE_FLOAT_EPSILON 0.00001

NS_CC_YHGE_BEGIN

static inline bool fuzzyEqualf(float a, float b)
{
    return a-YHGE_FLOAT_EPSILON <=b && b<= a+YHGE_FLOAT_EPSILON;
    
//    return fabs(a-b)<=YHGE_FLOAT_EPSILON;
}

static inline bool fuzzyEqual(double a, double b)
{
    return a-YHGE_FLOAT_EPSILON <=b && b<= a+YHGE_FLOAT_EPSILON;
    
    //    return fabs(a-b)<=YHGE_FLOAT_EPSILON;
}

NS_CC_YHGE_END

#endif // YHGE_MATH_FLOATUTIL_H_