#include "ISOActiveLayerInfo.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

ISOActiveLayerInfo::ISOActiveLayerInfo()
:_name("")
,_offset(CCPointZero)
,_opacity(255)
,_visible(true)
,_layerSize(CCSizeZero)
{
}

ISOActiveLayerInfo::~ISOActiveLayerInfo()
{
    CCLOG("ISOActiveLayerInfo destroy");
}

NS_CC_YHGE_ISOMETRIC_END
