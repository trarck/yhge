#include "ISOObjectInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOObjectInfo::ISOObjectInfo()
:_sName("")
,_sType("")
,_uGid(0)
,_tPosition(CCPointZero)
,_tSize(CCSizeZero)
,_fRotation(0.0f)
,_bVisible(true)
{
    _pProperties=new CCDictionary();
}

ISOObjectInfo::~ISOObjectInfo()
{
    CCLOG("ISOObjectInfo destroy");
    CC_SAFE_RELEASE(_pProperties);
}

NS_CC_YHGE_ISOMETRIC_END
