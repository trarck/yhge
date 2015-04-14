#include "ISOTilesetInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTilesetInfo::ISOTilesetInfo()
:_sName("")
,_uFirstGid(0)
,_sSourceFile("")
,_tTileSize(CCSizeZero)
,_uSpacing(0)
,_uMargin(0)
,_tTileOffset(CCPointZero)
,_sImageSource("")
,_tImageSize(CCSizeZero)
,_pProperties(NULL)
,_pTiles(NULL)
{
    _pProperties=new CCDictionary();
    _pTiles=new CCArray();
    _pTiles->init();
}

ISOTilesetInfo::~ISOTilesetInfo()
{
    CCLOG("ISOTilesetInfo destroy");
    CC_SAFE_RELEASE(_pProperties);
    CC_SAFE_RELEASE(_pTiles);
}

NS_CC_YHGE_ISOMETRIC_END
