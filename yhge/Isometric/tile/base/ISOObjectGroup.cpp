#include "ISOObjectGroup.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

//implementation ISOObjectGroup

ISOObjectGroup::ISOObjectGroup()
:_offset(CCPointZero)
,_name("")
,_objects(NULL)
,_properties(NULL)
{
    
}

ISOObjectGroup::~ISOObjectGroup()
{
    CCLOGINFO( "ISOObjectGroup: deallocing.");
    CC_SAFE_RELEASE(_objects);
    CC_SAFE_RELEASE(_properties);
}

bool ISOObjectGroup::init()
{
    _objects = new CCArray();
    _objects->init();
    _properties = new CCDictionary();
    return true;
}

CCDictionary* ISOObjectGroup::objectNamed(const char *objectName)
{
    if (_objects && _objects->count() > 0)
    {
        Ref* pObj = NULL;
        CCARRAY_FOREACH(_objects, pObj)
        {
            CCDictionary* pDict = (CCDictionary*)pObj;
            CCString *name = (CCString*)pDict->objectForKey("name");
            if (name && name->_string == objectName)
            {
                return pDict;
            }
        }
    }
    // object not found
    return NULL;    
}

Value ISOObjectGroup::getProperty(const std::string& propertyName)
{
	if (_properties.find(propertyName) != _properties.end())
		return _properties.at(propertyName);

	return Value::Null;
}

void ISOObjectGroup::seoffset(const Vec2& offset)
{
    _offset = offset;
}

const Vec2& ISOObjectGroup::geoffset()
{
    return _offset;
}

void ISOObjectGroup::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(_properties);
    _properties = pProperties;
}

CCDictionary* ISOObjectGroup::getProperties()
{
    return _properties;
}

void ISOObjectGroup::setObjects(CCArray* objects)
{
    CC_SAFE_RETAIN(objects);
    CC_SAFE_RELEASE(_objects);
    _objects = objects;
}

CCArray* ISOObjectGroup::getObjects()
{
    return _objects;
}
NS_CC_YHGE_ISOMETRIC_END
