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
    
    /**
     * 设置
     */
	virtual void setup(void);
    
    /**
     * 清理
     */
	virtual void cleanup(void);

    /**
     * 注册消息
     */
    virtual bool registerMessages();
    
    /**
     * 清理消息
     */
	virtual void cleanupMessages();
    
    //使用GameEntity也没有意义，具体还要使用强制类型转换
    //弱连接
	inline void setOwner(CCObject* owner)
	{
		m_owner = owner;
	}

	inline CCObject* getOwner()
	{
		return m_owner;
	}

	inline void setName(const std::string& name)
	{
		m_name = name;
	}

	inline const std::string& getName()
	{
		return m_name;
	}
protected:
    
    //名称
    std::string m_name;
    
    //弱引用
    CCObject* m_owner;
    
	
};

NS_CC_YHGE_END

#endif // YHGE_COMPONENTS_COMPONENT_H_
