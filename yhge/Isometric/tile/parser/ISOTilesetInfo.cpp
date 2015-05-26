#include "ISOTilesetInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTilesetInfo::ISOTilesetInfo()
:_name("")
,_uFirstGid(0)
,_sSourceFile("")
,_tTileSize(CCSizeZero)
,_uSpacing(0)
,_uMargin(0)
,_tTileOffset(CCPointZero)
,_sImageSource("")
,_tImageSize(CCSizeZero)
,_properties(NULL)
,_pTiles(NULL)
{
    _properties=new CCDictionary();
    _pTiles=new CCArray();
    _pTiles->init();
}

ISOTilesetInfo::~ISOTilesetInfo()
{
    CCLOG("ISOTilesetInfo destroy");
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_pTiles);
}

NS_CC_YHGE_ISOMETRIC_END
