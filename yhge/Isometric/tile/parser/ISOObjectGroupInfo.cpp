#include "ISOObjectGroupInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOObjectGroupInfo::ISOObjectGroupInfo()
:_name("")
,_color(ccWHITE)
,_opacity(255)
,_visible(true)
,_positionOffset(CCPointZero)
,_objects(NULL)
,_properties(NULL)
{
    _properties=new CCDictionary();
    _objects=new CCArray();
    _objects->init();
}

ISOObjectGroupInfo::~ISOObjectGroupInfo()
{
    CCLOG("ISOObjectGroupInfo destroy");
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_objects);
}

NS_CC_YHGE_ISOMETRIC_END
