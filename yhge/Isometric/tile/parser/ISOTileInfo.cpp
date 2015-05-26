#include "ISOTileInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileInfo::ISOTileInfo()
:_uId(0)
,_sImageSource("")
,_tImageSize(CCSizeZero)
{
    _properties=new CCDictionary();
}

ISOTileInfo::~ISOTileInfo()
{
    CCLOG("ISOTileInfo destroy");
    CC_SAFE_RELEASE(_properties);
}

NS_CC_YHGE_ISOMETRIC_END
