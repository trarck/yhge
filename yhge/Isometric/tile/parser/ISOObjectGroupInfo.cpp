#include "ISOObjectGroupInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOObjectGroupInfo::ISOObjectGroupInfo()
:_sName("")
,_tColor(ccWHITE)
,_cOpacity(255)
,_bVisible(true)
,_tPositionOffset(CCPointZero)
,_pObjects(NULL)
,_pProperties(NULL)
{
    _pProperties=new CCDictionary();
    _pObjects=new CCArray();
    _pObjects->init();
}

ISOObjectGroupInfo::~ISOObjectGroupInfo()
{
    CCLOG("ISOObjectGroupInfo destroy");
    CC_SAFE_RELEASE(_pProperties);
    CC_SAFE_RELEASE(_pObjects);
}

NS_CC_YHGE_ISOMETRIC_END
