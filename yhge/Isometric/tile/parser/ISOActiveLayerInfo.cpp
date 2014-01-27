#include "ISOActiveLayerInfo.h"

NS_CC_YHGE_BEGIN

ISOActiveLayerInfo::ISOActiveLayerInfo()
:m_sName("")
,m_tOffset(CCPointZero)
,m_cOpacity(255)
,m_pProperties(NULL)
,m_bVisible(true)
,m_tLayerSize(CCSizeZero)
,m_objects(NULL)
{
    m_pProperties=new CCDictionary();
    m_objects=new CCArray();
}

ISOActiveLayerInfo::~ISOActiveLayerInfo()
{
    CCLOG("ISOActiveLayerInfo destroy");
    CC_SAFE_RELEASE_NULL(m_pProperties);
    CC_SAFE_RELEASE_NULL(m_objects);
}

NS_CC_YHGE_END
