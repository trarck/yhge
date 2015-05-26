#include "ISOLayerInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOLayerInfo::ISOLayerInfo()
:_name("")
,_pTiles(NULL)
,_offset(CCPointZero)
,_opacity(255)
,_bOwnTiles(true)
,_properties(NULL)
,_visible(true)
,_layerSize(CCSizeZero)
{
    _properties=new CCDictionary();
}

ISOLayerInfo::~ISOLayerInfo()
{
    CCLOG("ISOLayerInfo destroy");
    CC_SAFE_RELEASE(_properties);
    if(_bOwnTiles && _pTiles )
    {
        delete [] _pTiles;
        _pTiles = NULL;
    }
}

NS_CC_YHGE_ISOMETRIC_END
