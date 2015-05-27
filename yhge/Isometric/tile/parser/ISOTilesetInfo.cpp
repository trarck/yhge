#include "ISOTilesetInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTilesetInfo::ISOTilesetInfo()
:_name("")
,_uFirstGid(0)
,_sourceFile("")
,_tileSize(CCSizeZero)
,_uSpacing(0)
,_uMargin(0)
,_tileOffset(CCPointZero)
,_imageSource("")
,_imageSize(CCSizeZero)
{
}

ISOTilesetInfo::~ISOTilesetInfo()
{
    CCLOG("ISOTilesetInfo destroy");
}

NS_CC_YHGE_ISOMETRIC_END
