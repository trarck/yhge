#include "ISOTileObject.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileObject::ISOTileObject()
:_uGid(0)
,_name("")
,_type("")
,_position(CCPointZero)
,_size(CCSizeZero)
,_visible(true)
,_parts(NULL)
,_properties(NULL)
{

}


ISOTileObject::~ISOTileObject()
{
    CCLOG("ISOTileObject destroy");
    CC_SAFE_RELEASE_NULL(_properties);
    CC_SAFE_RELEASE_NULL(_parts);
}

bool ISOTileObject::init()
{
    _properties = new CCDictionary();
    _parts=new CCArray();
    _parts->init();
    return true;
}

void ISOTileObject::setType(const char * pType)
{
    _type = pType;
}

std::string& ISOTileObject::getType()
{
    return _type;
}

void ISOTileObject::seposition(Vec2 position)
{
    _position = position;
}

Vec2 ISOTileObject::geposition()
{
    return _position;
}

void ISOTileObject::sesize(Size size)
{
    _size = size;
}

Size ISOTileObject::gesize()
{
    return _size;
}

void ISOTileObject::setGid(unsigned int uGid)
{
    _uGid = uGid;
}

unsigned int ISOTileObject::getGid()
{
    return _uGid;
}

void ISOTileObject::setVisible(bool visible)
{
    _visible = visible;
}

bool ISOTileObject::getVisible()
{
    return _visible;
}

void ISOTileObject::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(_properties);
    _properties=pProperties;
    
}

CCDictionary* ISOTileObject::getProperties()
{
    return _properties;
}

NS_CC_YHGE_ISOMETRIC_END
