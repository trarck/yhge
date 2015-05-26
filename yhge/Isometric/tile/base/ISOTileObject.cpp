#include "ISOTileObject.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileObject::ISOTileObject()
:_uGid(0)
,_name("")
,_sType("")
,_tPosition(CCPointZero)
,_tSize(CCSizeZero)
,_visible(true)
,_pParts(NULL)
,_properties(NULL)
{

}


ISOTileObject::~ISOTileObject()
{
    CCLOG("ISOTileObject destroy");
    CC_SAFE_RELEASE_NULL(_properties);
    CC_SAFE_RELEASE_NULL(_pParts);
}

bool ISOTileObject::init()
{
    _properties = new CCDictionary();
    _pParts=new CCArray();
    _pParts->init();
    return true;
}

void ISOTileObject::setType(const char * pType)
{
    _sType = pType;
}

std::string& ISOTileObject::getType()
{
    return _sType;
}

void ISOTileObject::setPosition(Vec2 tPosition)
{
    _tPosition = tPosition;
}

Vec2 ISOTileObject::getPosition()
{
    return _tPosition;
}

void ISOTileObject::setSize(Size tSize)
{
    _tSize = tSize;
}

Size ISOTileObject::getSize()
{
    return _tSize;
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
