#include "ISOTileObject.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileObject::ISOTileObject()
:_gid(0)
,_name("")
,_type("")
,_position(CCPointZero)
,_size(CCSizeZero)
,_visible(true)
{

}


ISOTileObject::~ISOTileObject()
{
    CCLOG("ISOTileObject destroy");
}

bool ISOTileObject::init()
{
    return true;
}
NS_CC_YHGE_ISOMETRIC_END
