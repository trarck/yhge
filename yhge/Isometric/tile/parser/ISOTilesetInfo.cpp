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
,_properties(NULL)
,_tiles(NULL)
{
    _properties=new CCDictionary();
    _tiles=new CCArray();
    _tiles->init();
}

ISOTilesetInfo::~ISOTilesetInfo()
{
    CCLOG("ISOTilesetInfo destroy");
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_tiles);
}

NS_CC_YHGE_ISOMETRIC_END
