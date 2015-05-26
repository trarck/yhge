﻿#include "ISOObjectInfo.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOObjectInfo::ISOObjectInfo()
:_name("")
,_sType("")
,_uGid(0)
,_tPosition(CCPointZero)
,_tSize(CCSizeZero)
,_fRotation(0.0f)
,_visible(true)
{
    _properties=new CCDictionary();
}

ISOObjectInfo::~ISOObjectInfo()
{
    CCLOG("ISOObjectInfo destroy");
    CC_SAFE_RELEASE(_properties);
}

NS_CC_YHGE_ISOMETRIC_END
