#ifndef YHGE_ENTITYCOMPONENT_ENTITY_H_
#define YHGE_ENTITYCOMPONENT_ENTITY_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

class Component;

/**
 * 组件系统基类
 */
class Entity : public CCObject
{
public:
    
    Entity();
    
    virtual ~Entity();
    
    virtual bool init(void);
    
    CREATE_FUNC(Entity);
    
    //==========================组件操作====================//
    /**
     * 取得第一个名子为name的组件
     */
    virtual Component* getComponent(const std::string& name);
    
    /**
     * 取得所有名子为name的组件
     */
    virtual CCArray* getComponents(const std::string& name);
    
    /**
     * 添加一个组件
     */
    virtual void addComponent(Component* component);
    
    /**
     * 添加一个组件，并把组件的名称设置为name
     */
    virtual void addComponent(Component* component,const std::string& name);
    
    /**
     * 移除所有名子为name的组件
     */
    virtual void removeComponent(const std::string& name);
    
    /**
     * 移除一个具体的组件
     */
    virtual void removeComponent(Component* component);
    
    /**
     * 移除所有组件
     */
    virtual void removeComponents();
    
    /**
     * 清除组件
     */
    virtual void cleanupComponents();
    
    /**
     * 添加一个组件，不设置组件其它属性
     */
    virtual void addComponentOnly(Component* component);
    
    /**
     * 移除一个具体的组件，不设置组件其它属性
     */
    virtual void removeComponentOnly(Component* component);

public:
    
    inline void setComponents(CCArray* components)
    {
        CC_SAFE_RETAIN(components);
        CC_SAFE_RELEASE(m_components);
        m_components = components;
    }
    
    inline CCArray* getComponents()
    {
        return m_components;
    }
    
protected:
    
    CCArray* m_components;
	
};

NS_CC_YHGE_END

#endif // YHGE_ENTITYCOMPONENT_ENTITY_H_
