#include "ISOObjectGroupInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOObjectGroupInfo::ISOObjectGroupInfo()
:_name("")
,_tColor(ccWHITE)
,_opacity(255)
,_visible(true)
,_tPositionOffset(CCPointZero)
,_pObjects(NULL)
,_properties(NULL)
{
    _properties=new CCDictionary();
    _pObjects=new CCArray();
    _pObjects->init();
}

ISOObjectGroupInfo::~ISOObjectGroupInfo()
{
    CCLOG("ISOObjectGroupInfo destroy");
    CC_SAFE_RELEASE(_properties);
    CC_SAFE_RELEASE(_pObjects);
}

NS_CC_YHGE_ISOMETRIC_END
