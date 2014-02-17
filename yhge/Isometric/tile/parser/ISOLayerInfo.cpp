#include "ISOLayerInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOLayerInfo::ISOLayerInfo()
:m_sName("")
,m_pTiles(NULL)
,m_tOffset(CCPointZero)
,m_cOpacity(255)
,m_bOwnTiles(true)
,m_pProperties(NULL)
,m_bVisible(true)
,m_tLayerSize(CCSizeZero)
{
    m_pProperties=new CCDictionary();
}

ISOLayerInfo::~ISOLayerInfo()
{
    CCLOG("ISOLayerInfo destroy");
    CC_SAFE_RELEASE(m_pProperties);
    if(m_bOwnTiles && m_pTiles )
    {
        delete [] m_pTiles;
        m_pTiles = NULL;
    }
}

NS_CC_YHGE_ISOMETRIC_END
