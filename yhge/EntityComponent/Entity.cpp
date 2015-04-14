#include "Entity.h"
#include <yhge/Base/Log.h>
#include "Components/Component.h"

NS_CC_YHGE_BEGIN

Entity::Entity()
:_entityId(0)
,_components(NULL)
,_properties(NULL)
{
    YHDEBUG("Entity create");
}

Entity::~Entity()
{
    YHDEBUG("Entity destroy");
    CC_SAFE_RELEASE_NULL(_components);
    CC_SAFE_RELEASE_NULL(_properties);
}

bool Entity::init(void)
{
    YHDEBUG("Entity init");
    _components=new CCArray();
    _properties=new CCDictionary();
    return true;
}

//==========================组件操作====================//
/**
 * 取得第一个名子为name的组件
 */
Component* Entity::getComponent(const std::string& name)
{
    Ref* pObj=NULL;
    Component* component=NULL;
    CCARRAY_FOREACH(_components, pObj){
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
    
    Ref* pObj=NULL;
    Component* component=NULL;
    
    CCARRAY_FOREACH(_components, pObj){
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
    _components->addObject(component);
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
    Ref* pObj=NULL;
    Component* component=NULL;
    CCARRAY_FOREACH_REVERSE(_components, pObj){
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
    _components->removeObject(component);
}

/**
 * 移除所有组件
 */
void Entity::removeComponents()
{
    cleanupComponents();
    _components->removeAllObjects();
}

/**
 * 清除组件
 */
void Entity::cleanupComponents()
{
    Ref* pObj=NULL;
    Component* component=NULL;
    CCARRAY_FOREACH_REVERSE(_components, pObj){
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
    _components->addObject(component);
}

/**
 * 移除一个具体的组件，不设置组件其它属性
 */
void Entity::removeComponentOnly(Component* component)
{
    _components->removeObject(component);
}

//==========================属性操作====================//
/**
 * 取得第一个名子为name的组件
 */
Property* Entity::getProperty(const std::string& name)
{
    return static_cast<Property*>(_properties->objectForKey(name));
}

/**
 * 添加一个组件，并把组件的名称设置为name
 */
void Entity::addProperty(Property* property,const std::string& name)
{
    _properties->setObject(property, name);
}

/**
 * 移除所有名子为name的组件
 */
void Entity::removeProperty(const std::string& name)
{
    _properties->removeObjectForKey(name);
}

/**
 * 移除一个具体的组件
 */
void Entity::removeProperty(Property* property)
{
    CCDictElement* pElem=NULL;

    CCDICT_FOREACH(_properties, pElem){
        if (pElem->getObject()==property) {
            _properties->removeObjectForKey(pElem->getStrKey());
        }
    }
}

/**
 * 移除所有组件
 */
void Entity::removeProperties()
{
    _properties->removeAllObjects();
}

void Entity::cleanup()
{
    cleanupComponents();
}

NS_CC_YHGE_END
