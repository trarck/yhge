#include "ISOTileObject.h"


NS_CC_YHGE_ISOMETRIC_BEGIN

ISOTileObject::ISOTileObject()
:m_uGid(0)
,m_sName("")
,m_sType("")
,m_tPosition(CCPointZero)
,m_tSize(CCSizeZero)
,m_bVisible(true)
,m_pParts(NULL)
,m_pProperties(NULL)
{

}


ISOTileObject::~ISOTileObject()
{
    CCLOG("ISOTileObject destroy");
    CC_SAFE_RELEASE_NULL(m_pProperties);
    CC_SAFE_RELEASE_NULL(m_pParts);
}

bool ISOTileObject::init()
{
    m_pProperties = new CCDictionary();
    m_pParts=new CCArray();
    m_pParts->init();
    return true;
}

void ISOTileObject::setType(const char * pType)
{
    m_sType = pType;
}

std::string& ISOTileObject::getType()
{
    return m_sType;
}

void ISOTileObject::setPosition(CCPoint tPosition)
{
    m_tPosition = tPosition;
}

CCPoint ISOTileObject::getPosition()
{
    return m_tPosition;
}

void ISOTileObject::setSize(CCSize tSize)
{
    m_tSize = tSize;
}

CCSize ISOTileObject::getSize()
{
    return m_tSize;
}

void ISOTileObject::setGid(unsigned int uGid)
{
    m_uGid = uGid;
}

unsigned int ISOTileObject::getGid()
{
    return m_uGid;
}

void ISOTileObject::setVisible(bool bVisible)
{
    m_bVisible = bVisible;
}

bool ISOTileObject::getVisible()
{
    return m_bVisible;
}

void ISOTileObject::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties=pProperties;
    
}

CCDictionary* ISOTileObject::getProperties()
{
    return m_pProperties;
}

NS_CC_YHGE_ISOMETRIC_END
