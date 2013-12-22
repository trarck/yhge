#include "ISOObjectGroup.h"
#include "ccMacros.h"

NS_CC_YHGE_BEGIN

//implementation ISOObjectGroup

ISOObjectGroup::ISOObjectGroup()
:m_tOffset(CCPointZero)
,m_sName("")
,m_pObjects(NULL)
,m_pProperties(NULL)
{
    
}

ISOObjectGroup::~ISOObjectGroup()
{
    CCLOGINFO( "ISOObjectGroup: deallocing.");
    CC_SAFE_RELEASE(m_pObjects);
    CC_SAFE_RELEASE(m_pProperties);
}

bool ISOObjectGroup::init()
{
    m_pObjects = new CCArray();
    m_pObjects->init();
    m_pProperties = new CCDictionary();
    return true;
}

CCDictionary* ISOObjectGroup::objectNamed(const char *objectName)
{
    if (m_pObjects && m_pObjects->count() > 0)
    {
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pObjects, pObj)
        {
            CCDictionary* pDict = (CCDictionary*)pObj;
            CCString *name = (CCString*)pDict->objectForKey("name");
            if (name && name->m_sString == objectName)
            {
                return pDict;
            }
        }
    }
    // object not found
    return NULL;    
}

CCString* ISOObjectGroup::propertyNamed(const char* propertyName)
{
    return (CCString*)m_pProperties->objectForKey(propertyName);
}

void ISOObjectGroup::setOffset(const CCPoint& tOffset)
{
    m_tOffset = tOffset;
}

const CCPoint& ISOObjectGroup::getOffset()
{
    return m_tOffset;
}

void ISOObjectGroup::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* ISOObjectGroup::getProperties()
{
    return m_pProperties;
}

void ISOObjectGroup::setObjects(CCArray* pObjects)
{
    CC_SAFE_RETAIN(pObjects);
    CC_SAFE_RELEASE(m_pObjects);
    m_pObjects = pObjects;
}

CCArray* ISOObjectGroup::getObjects()
{
    return m_pObjects;
}
NS_CC_YHGE_END
