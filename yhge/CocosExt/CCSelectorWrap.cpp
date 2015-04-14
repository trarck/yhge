#include "CCSelectorWrap.h"

NS_CC_YHGE_BEGIN

CCSelectorWrap::~CCSelectorWrap()
{
    CC_SAFE_RELEASE(_target);
    CC_SAFE_RELEASE(_data);
}

NS_CC_YHGE_END