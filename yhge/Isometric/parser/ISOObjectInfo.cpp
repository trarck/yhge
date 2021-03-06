#include "ISOObjectInfo.h"


NS_CC_YHGE_BEGIN

ISOObjectInfo::ISOObjectInfo()
:m_sName("")
,m_sType("")
,m_uGid(0)
,m_tPosition(CCPointZero)
,m_tSize(CCSizeZero)
,m_bVisible(true)
{
    m_pProperties=new CCDictionary();
}

ISOObjectInfo::~ISOObjectInfo()
{
    CCLOG("ISOObjectInfo destroy");
    CC_SAFE_RELEASE(m_pProperties);
}

NS_CC_YHGE_END
