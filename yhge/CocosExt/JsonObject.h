#ifndef YHGE_COCOSEXT_JSONOBJECT_H_
#define YHGE_COCOSEXT_JSONOBJECT_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Jsoncpp/json.h>

NS_CC_YHGE_BEGIN

/**
 * 把json值包装成 cocos object
 * 避免值对象的copy
 */
class JsonObject : public cocos2d::Ref
{
public:
	inline JsonObject()
    :_value(Json::nullValue)
	{
		
	}
	
    inline JsonObject(const Json::Value& value)
    :_value(value)
    {
        
    }
    
    ~JsonObject()
    {
        
    }
    
    
    inline void setValue(const Json::Value& value){
        _value=value;
    }
    
    inline const Json::Value& getValue()
    {
        return _value;
    }
	
    inline static JsonObject* create()
	{
		JsonObject* pRet=new JsonObject();
		pRet->autorelease();
		return pRet;
	}
    
	inline static JsonObject* create(const Json::Value& value)
	{
		JsonObject* pRet=new JsonObject(value);
		pRet->autorelease();
		return pRet;
	}
       
    inline Json::Value &operator[]( Json::UInt index )
    {
        return _value[index];
    }

    const Json::Value &operator[]( Json::UInt index ) const
    {
        return _value[index];
    }
    
    Json::Value &operator[]( const char *key )
    {
        return _value[key];
    }

    const Json::Value &operator[]( const char *key ) const
    {
        return _value[key];
    }

    Json::Value &operator[]( const std::string &key )
    {
        return _value[key];
    }

    const Json::Value &operator[]( const std::string &key ) const
    {
        return _value[key];
    }
    
    
private:
    
    JsonObject(const JsonObject& other);
    JsonObject& operator= (const JsonObject& other);
    
private:
    
	Json::Value _value;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_JSONOBJECT_H_
