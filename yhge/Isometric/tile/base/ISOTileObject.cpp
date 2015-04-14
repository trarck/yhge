#include "ISOTileObject.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileObject::ISOTileObject()
:_uGid(0)
,_sName("")
,_sType("")
,_tPosition(CCPointZero)
,_tSize(CCSizeZero)
,_bVisible(true)
,_pParts(NULL)
,_pProperties(NULL)
{

}


ISOTileObject::~ISOTileObject()
{
    CCLOG("ISOTileObject destroy");
    CC_SAFE_RELEASE_NULL(_pProperties);
    CC_SAFE_RELEASE_NULL(_pParts);
}

bool ISOTileObject::init()
{
    _pProperties = new CCDictionary();
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

void ISOTileObject::setPosition(CCPoint tPosition)
{
    _tPosition = tPosition;
}

CCPoint ISOTileObject::getPosition()
{
    return _tPosition;
}

void ISOTileObject::setSize(CCSize tSize)
{
    _tSize = tSize;
}

CCSize ISOTileObject::getSize()
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

void ISOTileObject::setVisible(bool bVisible)
{
    _bVisible = bVisible;
}

bool ISOTileObject::getVisible()
{
    return _bVisible;
}

void ISOTileObject::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(_pProperties);
    _pProperties=pProperties;
    
}

CCDictionary* ISOTileObject::getProperties()
{
    return _pProperties;
}

NS_CC_YHGE_ISOMETRIC_END
