#ifndef YHGE_COMPONENTS_COMPONENT_H_
#define YHGE_COMPONENTS_COMPONENT_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <yhge/Message/Message.h>

NS_CC_YHGE_BEGIN

//typedef CCObject GameEntity;

class Component : public CCObject
{
public:
    Component();
    ~Component();
    
    virtual bool init(void);  
    
	virtual void setup(void);
	virtual void cleanup(void);

    virtual bool registerMessages();
	virtual void cleanupMessages();
    //使用GameEntity也没有意义，具体还要使用强制类型转换
    //弱连接
	inline void setOwner(CCObject* pOwner)
	{
		CC_SAFE_RETAIN(pOwner);
		CC_SAFE_RELEASE(m_pOwner);
		m_pOwner = pOwner;
	}

	inline CCObject* getOwner()
	{
		return m_pOwner;
	}

	inline void setName(const std::string& sName)
	{
		m_sName = sName;
	}

	inline const std::string& getName()
	{
		return m_sName;
	}
protected:
    CCObject* m_pOwner;
	std::string m_sName;
};

NS_CC_YHGE_END

#endif // YHGE_COMPONENTS_COMPONENT_H_
