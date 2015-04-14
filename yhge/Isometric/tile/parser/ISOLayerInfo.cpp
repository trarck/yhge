#include "ISOLayerInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOLayerInfo::ISOLayerInfo()
:_sName("")
,_pTiles(NULL)
,_tOffset(CCPointZero)
,_cOpacity(255)
,_bOwnTiles(true)
,_pProperties(NULL)
,_bVisible(true)
,_tLayerSize(CCSizeZero)
{
    _pProperties=new CCDictionary();
}

ISOLayerInfo::~ISOLayerInfo()
{
    CCLOG("ISOLayerInfo destroy");
    CC_SAFE_RELEASE(_pProperties);
    if(_bOwnTiles && _pTiles )
    {
        delete [] _pTiles;
        _pTiles = NULL;
    }
}

NS_CC_YHGE_ISOMETRIC_END
