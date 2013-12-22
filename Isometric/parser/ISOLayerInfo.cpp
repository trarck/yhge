#include "ISOLayerInfo.h"

NS_CC_YHGE_BEGIN

ISOLayerInfo::ISOLayerInfo()
:m_sName("")
,m_pTiles(NULL)
,m_tOffset(CCPointZero)
,m_cOpacity(255)
{
    m_pProperties=new CCDictionary();
}

ISOLayerInfo::~ISOLayerInfo()
{
    CCLOG("ISOLayerInfo destroy");
    CC_SAFE_RELEASE(m_pProperties);
    if( m_pTiles )
    {
        delete [] m_pTiles;
        m_pTiles = NULL;
    }
}

NS_CC_YHGE_END
