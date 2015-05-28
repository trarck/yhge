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
{

}


ISOMapObject::~ISOMapObject()
{
    CCLOG("ISOMapObject destroy");
}

bool ISOMapObject::init()
{
    return true;
}

NS_CC_YHGE_ISOMETRIC_END
