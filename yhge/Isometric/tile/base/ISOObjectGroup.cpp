#include "ISOObjectGroup.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

//implementation ISOObjectGroup

ISOObjectGroup::ISOObjectGroup()
:_offset(CCPointZero)
,_name("")
{
    
}

ISOObjectGroup::~ISOObjectGroup()
{
    CCLOGINFO( "ISOObjectGroup: deallocing.");
}

bool ISOObjectGroup::init()
{
    return true;
}

ISOMapObject* ISOObjectGroup::getObject(const std::string& objectName)
{
	for (ISOMapObjectVector::iterator iter = _objects.begin(); iter != _objects.end(); ++iter){

		if ((*iter)->getName() == objectName){
			return *iter;
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

NS_CC_YHGE_ISOMETRIC_END
