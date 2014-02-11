#include "Entity.h"

#include "Components/Component.h"

NS_CC_YHGE_BEGIN

Entity::Entity()
:m_components(NULL)
,m_properties(NULL)
{
    CCLOG("Entity create");
}

Entity::~Entity()
{
    CCLOG("Entity destroy");
    CC_SAFE_RELEASE_NULL(m_components);
    CC_SAFE_RELEASE_NULL(m_properties);
}

bool Entity::init(void)
{
    CCLOG("Entity init");
    m_components=new CCArray();
    m_properties=new CCDictionary();
    return true;
}

//==========================组件操作====================//
/**
 * 取得第一个名子为name的组件
 */
Component* Entity::getComponent(const std::string& name)
{
    CCObject* pObj=NULL;
    Component* component=NULL;
    CCARRAY_FOREACH(m_components, pObj){
        component=static_cast<Component*>(pObj);
        if (component->getName()==name) {
            return component;
        }
    }
    return NULL;
}

/**
 * 取得所有名子为name的组件
 */
CCArray* Entity::getComponents(const std::string& name)
{
    CCArray* components=CCArray::create();
    
    CCObject* pObj=NULL;
    Component* component=NULL;
    
    CCARRAY_FOREACH(m_components, pObj){
        component=static_cast<Component*>(pObj);
        if (component->getName()==name) {
            components->addObject(component);
        }
    }
    
    return components;
}

/**
 * 添加一个组件
 */
void Entity::addComponent(Component* component)
{
    component->setOwner(this);
    component->setup();
    m_components->addObject(component);
}

/**
 * 添加一个组件，并把组件的名称设置为name
 */
void Entity::addComponent(Component* component,const std::string& name)
{
    component->setName(name);
    addComponent(component);
}

/**
 * 移除所有名子为name的组件
 */
void Entity::removeComponent(const std::string& name)
{
    CCObject* pObj=NULL;
    Component* component=NULL;
    CCARRAY_FOREACH_REVERSE(m_components, pObj){
        component=static_cast<Component*>(pObj);
        if (component->getName()==name) {
            this->removeComponent(component);
        }
    }
}

/**
 * 移除一个具体的组件
 */
void Entity::removeComponent(Component* component)
{
    component->cleanup();
    component->setOwner(NULL);
    m_components->removeObject(component);
}

/**
 * 移除所有组件
 */
void Entity::removeComponents()
{
    cleanupComponents();
    m_components->removeAllObjects();
}

/**
 * 清除组件
 */
void Entity::cleanupComponents()
{
    CCObject* pObj=NULL;
    Component* component=NULL;
    CCARRAY_FOREACH_REVERSE(m_components, pObj){
        component=static_cast<Component*>(pObj);
        component->cleanup();
        component->setOwner(NULL);
    }
}

/**
 * 添加一个组件，不设置组件其它属性
 */
void Entity::addComponentOnly(Component* component)
{
    m_components->addObject(component);
}

/**
 * 移除一个具体的组件，不设置组件其它属性
 */
void Entity::removeComponentOnly(Component* component)
{
    m_components->removeObject(component);
}

//==========================属性操作====================//
/**
 * 取得第一个名子为name的组件
 */
Property* Entity::getProperty(const std::string& name)
{
    return static_cast<Property*>(m_properties->objectForKey(name));
}

/**
 * 添加一个组件，并把组件的名称设置为name
 */
void Entity::addProperty(Property* property,const std::string& name)
{
    m_properties->setObject(property, name);
}

/**
 * 移除所有名子为name的组件
 */
void Entity::removeProperty(const std::string& name)
{
    m_properties->removeObjectForKey(name);
}

/**
 * 移除一个具体的组件
 */
void Entity::removeProperty(Property* property)
{
    CCDictElement* pElem=NULL;

    CCDICT_FOREACH(m_properties, pElem){
        if (pElem->getObject()==property) {
            m_properties->removeObjectForKey(pElem->getStrKey());
        }
    }
}

/**
 * 移除所有组件
 */
void Entity::removeProperties()
{
    m_properties->removeAllObjects();
}

NS_CC_YHGE_END
