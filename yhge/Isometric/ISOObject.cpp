#include "ISOObject.h"


NS_CC_YHGE_BEGIN

ISOObject::ISOObject()
:m_uGid(0)
{
    m_pProperties=new CCDictionary();
}


ISOObject::~ISOObject()
{
    CCLOG("ISOObject destroy");
    CC_SAFE_RELEASE(m_pProperties);
}

bool ISOObject::init()
{
    m_pProperties = new CCDictionary();
    return true;
}

void ISOObject::setType(const char * pType)
{
    m_sType = pType;
}

std::string& ISOObject::getType()
{
    return m_sType;
}

void ISOObject::setPosition(CCPoint tPosition)
{
    m_tPosition = tPosition;
}

CCPoint ISOObject::getPosition()
{
    return m_tPosition;
}

void ISOObject::setSize(CCSize tSize)
{
    m_tSize = tSize;
}

CCSize ISOObject::getSize()
{
    return m_tSize;
}

void ISOObject::setGid(unsigned int uGid)
{
    m_uGid = uGid;
}

unsigned int ISOObject::getGid()
{
    return m_uGid;
}

void ISOObject::setVisible(bool bVisible)
{
    m_bVisible = bVisible;
}

bool ISOObject::getVisible()
{
    return m_bVisible;
}

void ISOObject::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties=pProperties;
    
}

CCDictionary* ISOObject::getProperties()
{
    return m_pProperties;
}

NS_CC_YHGE_END
