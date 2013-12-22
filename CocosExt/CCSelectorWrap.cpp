#include "CCSelectorWrap.h"

NS_CC_YHGE_BEGIN

CCSelectorWrap::~CCSelectorWrap()
{
    CC_SAFE_RELEASE(m_pTarget);
    CC_SAFE_RELEASE(m_data);
}

NS_CC_YHGE_END