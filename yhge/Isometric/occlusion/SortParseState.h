
#ifndef YHGE_ISOMETRIC_SORTPARSESTATE_H_
#define YHGE_ISOMETRIC_SORTPARSESTATE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "SortZIndexNode.h"

NS_CC_YHGE_BEGIN

enum
{
    kParseStateIdle,
    kParseStateBig,
    kParseStateSmall,
    kParseStateEqual,
    kParseStateLeftBig,
    kParseStateLeftSmall,
    kParseStateLeftEqual,
    kParseStateRightBig,
    kParseStateRightSmall,
    kParseStateRightEqual
};

class SortParseState:public CCObject
{
public:
    virtual void enter();
    virtual void exit();
};

class SortParseStateIdle:public SortParseState
{
public:
    
};

class SortParseStateBig:public SortParseState
{
public:
    
};

class SortParseStateSmall:public SortParseState
{
public:
    
};

class SortParseStateEqual:public SortParseState
{
public:
    
};

class SortParseStateLeftBig:public SortParseState
{
public:
    
};

class SortParseStateLeftSmall:public SortParseState
{
public:
    
};

class SortParseStateLeftEqual:public SortParseState
{
public:
    
};

class SortParseStateRightBig:public SortParseState
{
public:
    
};

class SortParseStateRightSmall:public SortParseState
{
public:
    
};

class SortParseStateRightEqual:public SortParseState
{
public:
    
};

NS_CC_YHGE_END

#endif //YHGE_ISOMETRIC_SORTPARSESTATE_H_
