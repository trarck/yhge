#include "ISOTileInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileInfo::ISOTileInfo()
:m_uId(0)
,m_sImageSource("")
,m_tImageSize(CCSizeZero)
{
    m_pProperties=new CCDictionary();
}

ISOTileInfo::~ISOTileInfo()
{
    CCLOG("ISOTileInfo destroy");
    CC_SAFE_RELEASE(m_pProperties);
}

NS_CC_YHGE_ISOMETRIC_END
