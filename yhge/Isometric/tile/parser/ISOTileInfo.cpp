#include "ISOTileInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileInfo::ISOTileInfo()
:_uId(0)
,_imageSource("")
,_imageSize(CCSizeZero)
{
}

ISOTileInfo::~ISOTileInfo()
{
    CCLOG("ISOTileInfo destroy");
}

NS_CC_YHGE_ISOMETRIC_END
