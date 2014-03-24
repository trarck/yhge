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
class JsonObject : public cocos2d::CCObject
{
public:
	inline JsonObject()
    :m_value(Json::nullValue)
	{
		
	}
	
    inline JsonObject(const Json::Value& value)
    :m_value(value)
    {
        
    }
    
    ~JsonObject()
    {
        
    }
    
    
    inline void setValue(const Json::Value& value){
        m_value=value;
    }
    
    inline const Json::Value& getValue()
    {
        return m_value;
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
        return m_value[index];
    }

    const Json::Value &operator[]( Json::UInt index ) const
    {
        return m_value[index];
    }
    
    Json::Value &operator[]( const char *key )
    {
        return m_value[key];
    }

    const Json::Value &operator[]( const char *key ) const
    {
        return m_value[key];
    }

    Json::Value &operator[]( const std::string &key )
    {
        return m_value[key];
    }

    const Json::Value &operator[]( const std::string &key ) const
    {
        return m_value[key];
    }
    
    
private:
    
    JsonObject(const JsonObject& other);
    JsonObject& operator= (const JsonObject& other);
    
private:
    
	Json::Value m_value;
};


NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_JSONOBJECT_H_
