#include "ISOActiveLayerInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOActiveLayerInfo::ISOActiveLayerInfo()
:_name("")
,_offset(CCPointZero)
,_opacity(255)
,_properties(NULL)
,_visible(true)
,_layerSize(CCSizeZero)
,_objects(NULL)
{
    _properties=new CCDictionary();
    _objects=new CCArray();
}

ISOActiveLayerInfo::~ISOActiveLayerInfo()
{
    CCLOG("ISOActiveLayerInfo destroy");
    CC_SAFE_RELEASE_NULL(_properties);
    CC_SAFE_RELEASE_NULL(_objects);
}

NS_CC_YHGE_ISOMETRIC_END
