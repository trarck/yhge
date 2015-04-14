#include "ISOMapObject.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOMapObject::ISOMapObject()
:_uGid(0)
,_sName("")
,_sType("")
,_tPosition(CCPointZero)
,_tSize(CCSizeZero)
,_rotation(0)
,_bVisible(true)
,_pProperties(NULL)
{

}


ISOMapObject::~ISOMapObject()
{
    CCLOG("ISOMapObject destroy");
    CC_SAFE_RELEASE(_pProperties);
}

bool ISOMapObject::init()
{
    _pProperties = new CCDictionary();
    return true;
}

NS_CC_YHGE_ISOMETRIC_END
