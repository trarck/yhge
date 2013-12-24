#include "ISOObjectGroupInfo.h"


NS_CC_YHGE_BEGIN

ISOObjectGroupInfo::ISOObjectGroupInfo()
:m_sName("")
,m_tColor(ccWHITE)
{
    m_pProperties=new CCDictionary();
    m_pObjects=new CCArray();
}

ISOObjectGroupInfo::~ISOObjectGroupInfo()
{
    CCLOG("ISOObjectGroupInfo destroy");
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pObjects);
}

NS_CC_YHGE_END
