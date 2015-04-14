#include "ISOActiveLayerInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOActiveLayerInfo::ISOActiveLayerInfo()
:_sName("")
,_tOffset(CCPointZero)
,_cOpacity(255)
,_pProperties(NULL)
,_bVisible(true)
,_tLayerSize(CCSizeZero)
,_objects(NULL)
{
    _pProperties=new CCDictionary();
    _objects=new CCArray();
}

ISOActiveLayerInfo::~ISOActiveLayerInfo()
{
    CCLOG("ISOActiveLayerInfo destroy");
    CC_SAFE_RELEASE_NULL(_pProperties);
    CC_SAFE_RELEASE_NULL(_objects);
}

NS_CC_YHGE_ISOMETRIC_END
