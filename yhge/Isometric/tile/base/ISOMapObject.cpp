#include "ISOMapObject.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOMapObject::ISOMapObject()
:_gid(0)
,_name("")
,_type("")
,_position(CCPointZero)
,_size(CCSizeZero)
,_rotation(0)
,_visible(true)
,_properties(NULL)
{

}


ISOMapObject::~ISOMapObject()
{
    CCLOG("ISOMapObject destroy");
    CC_SAFE_RELEASE(_properties);
}

bool ISOMapObject::init()
{
    _properties = new CCDictionary();
    return true;
}

NS_CC_YHGE_ISOMETRIC_END
