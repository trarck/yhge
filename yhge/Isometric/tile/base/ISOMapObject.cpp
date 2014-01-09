#include "ISOMapObject.h"


NS_CC_YHGE_BEGIN

ISOMapObject::ISOMapObject()
:m_uGid(0)
,m_sName("")
,m_sType("")
,m_tPosition(CCPointZero)
,m_tSize(CCSizeZero)
,m_bVisible(true)
,m_pProperties(NULL)
{

}


ISOMapObject::~ISOMapObject()
{
    CCLOG("ISOMapObject destroy");
    CC_SAFE_RELEASE(m_pProperties);
}

bool ISOMapObject::init()
{
    m_pProperties = new CCDictionary();
    return true;
}

void ISOMapObject::setType(const char * pType)
{
    m_sType = pType;
}

std::string& ISOMapObject::getType()
{
    return m_sType;
}

void ISOMapObject::setPosition(CCPoint tPosition)
{
    m_tPosition = tPosition;
}

CCPoint ISOMapObject::getPosition()
{
    return m_tPosition;
}

void ISOMapObject::setSize(CCSize tSize)
{
    m_tSize = tSize;
}

CCSize ISOMapObject::getSize()
{
    return m_tSize;
}

void ISOMapObject::setGid(unsigned int uGid)
{
    m_uGid = uGid;
}

unsigned int ISOMapObject::getGid()
{
    return m_uGid;
}

void ISOMapObject::setVisible(bool bVisible)
{
    m_bVisible = bVisible;
}

bool ISOMapObject::getVisible()
{
    return m_bVisible;
}

void ISOMapObject::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties=pProperties;
    
}

CCDictionary* ISOMapObject::getProperties()
{
    return m_pProperties;
}

NS_CC_YHGE_END
