#include "ISOTileInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileInfo::ISOTileInfo()
:_uId(0)
,_sImageSource("")
,_tImageSize(CCSizeZero)
{
    _pProperties=new CCDictionary();
}

ISOTileInfo::~ISOTileInfo()
{
    CCLOG("ISOTileInfo destroy");
    CC_SAFE_RELEASE(_pProperties);
}

NS_CC_YHGE_ISOMETRIC_END
