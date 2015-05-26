#ifndef YHGE_COCOSEXT_SUPPORT_CCCOCOSVALUE_H_
#define YHGE_COCOSEXT_SUPPORT_CCCOCOSVALUE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN


#define COCOSVALUE_CREATE(type)\
static CocosValue* create(type v)\
{\
CocosValue* cocosValue=new CocosValue(v);\
if (cocosValue) {\
cocosValue->autorelease();\
return cocosValue;\
}\
return NULL;\
}

class CocosValue:public Ref
{
public:
	inline CocosValue()
		:_value(Value::Null)
	{

	}

	inline CocosValue(const Value& value)
		: _value(value)
	{

	}

	~CocosValue()
	{

	}


	inline void setValue(const Value& value){
		_value = value;
	}

	inline const Value& getValue()
	{
		return _value;
	}

	inline static CocosValue* create()
	{
		CocosValue* pRet = new CocosValue();
		pRet->autorelease();
		return pRet;
	}

	inline static CocosValue* create(const Value& value)
	{
		CocosValue* pRet = new CocosValue(value);
		pRet->autorelease();
		return pRet;
	}

    
private:
    
    Value _value;
};

NS_CC_YHGE_END


#endif /* defined(YHGE_COCOSEXT_SUPPORT_CCCOCOSVALUE_H_) */
