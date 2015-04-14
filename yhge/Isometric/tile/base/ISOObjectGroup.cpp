#include "ISOObjectGroup.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

//implementation ISOObjectGroup

ISOObjectGroup::ISOObjectGroup()
:_tOffset(CCPointZero)
,_sName("")
,_pObjects(NULL)
,_pProperties(NULL)
{
    
}

ISOObjectGroup::~ISOObjectGroup()
{
    CCLOGINFO( "ISOObjectGroup: deallocing.");
    CC_SAFE_RELEASE(_pObjects);
    CC_SAFE_RELEASE(_pProperties);
}

bool ISOObjectGroup::init()
{
    _pObjects = new CCArray();
    _pObjects->init();
    _pProperties = new CCDictionary();
    return true;
}

CCDictionary* ISOObjectGroup::objectNamed(const char *objectName)
{
    if (_pObjects && _pObjects->count() > 0)
    {
        Ref* pObj = NULL;
        CCARRAY_FOREACH(_pObjects, pObj)
        {
            CCDictionary* pDict = (CCDictionary*)pObj;
            CCString *name = (CCString*)pDict->objectForKey("name");
            if (name && name->_sString == objectName)
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
    return (CCString*)_pProperties->objectForKey(propertyName);
}

void ISOObjectGroup::setOffset(const CCPoint& tOffset)
{
    _tOffset = tOffset;
}

const CCPoint& ISOObjectGroup::getOffset()
{
    return _tOffset;
}

void ISOObjectGroup::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(_pProperties);
    _pProperties = pProperties;
}

CCDictionary* ISOObjectGroup::getProperties()
{
    return _pProperties;
}

void ISOObjectGroup::setObjects(CCArray* pObjects)
{
    CC_SAFE_RETAIN(pObjects);
    CC_SAFE_RELEASE(_pObjects);
    _pObjects = pObjects;
}

CCArray* ISOObjectGroup::getObjects()
{
    return _pObjects;
}
NS_CC_YHGE_ISOMETRIC_END
