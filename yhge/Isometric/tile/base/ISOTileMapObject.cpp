#include "ISOTileMapObject.h"


NS_CC_YHGE_BEGIN

ISOTileMapObject::ISOTileMapObject()
:m_uGid(0)
{
    m_pProperties=new CCDictionary();
}


ISOTileMapObject::~ISOTileMapObject()
{
    CCLOG("ISOTileMapObject destroy");
    CC_SAFE_RELEASE(m_pProperties);
}

bool ISOTileMapObject::init()
{
    m_pProperties = new CCDictionary();
    return true;
}

void ISOTileMapObject::setType(const char * pType)
{
    m_sType = pType;
}

std::string& ISOTileMapObject::getType()
{
    return m_sType;
}

void ISOTileMapObject::setPosition(CCPoint tPosition)
{
    m_tPosition = tPosition;
}

CCPoint ISOTileMapObject::getPosition()
{
    return m_tPosition;
}

void ISOTileMapObject::setSize(CCSize tSize)
{
    m_tSize = tSize;
}

CCSize ISOTileMapObject::getSize()
{
    return m_tSize;
}

void ISOTileMapObject::setGid(unsigned int uGid)
{
    m_uGid = uGid;
}

unsigned int ISOTileMapObject::getGid()
{
    return m_uGid;
}

void ISOTileMapObject::setVisible(bool bVisible)
{
    m_bVisible = bVisible;
}

bool ISOTileMapObject::getVisible()
{
    return m_bVisible;
}

void ISOTileMapObject::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties=pProperties;
    
}

CCDictionary* ISOTileMapObject::getProperties()
{
    return m_pProperties;
}

NS_CC_YHGE_END
