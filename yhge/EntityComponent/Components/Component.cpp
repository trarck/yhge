#include "Component.h"
#include <yhge/Message/MessageManager.h>

NS_CC_YHGE_BEGIN

Component::Component()
:m_name("")
,m_owner(NULL)
,m_type(0)
{
    CCLOG("Component[0x%lx] create",(unsigned long)this);
}

Component::Component(const std::string& name)
:m_name(name)
,m_owner(NULL)
{
    CCLOG("Component[0x%lx](%s) create",(unsigned long)this,m_name.c_str());
}

Component::~Component()
{
    CCLOG("Component[0x%lx](%s) destroy",(unsigned long)this,m_name.c_str());
}

bool Component::init(void)
{
    CCLOG("Component[0x%lx](%s) init",(unsigned long)this,m_name.c_str());
    return true;
}

void Component::setup(void)
{
    CCLOG("Component[0x%lx](%s)::setup",(unsigned long)this,m_name.c_str());
    this->registerMessages();
}

void Component::cleanup(void)
{
    CCLOG("Component[0x%lx](%s)::cleanup",(unsigned long)this,m_name.c_str());
    this->cleanupMessages();
}

bool Component::registerMessages()
{
    CCLOG("Component[0x%lx](%s)::registerMessages",(unsigned long)this,m_name.c_str());
    
    return true;
}

void Component::cleanupMessages()
{
    CCLOG("Component[0x%lx](%s)::cleanupMessages",(unsigned long)this,m_name.c_str());
}

/**
 * 组件被添加到entity
 */
void Component::onAddedToEntity()
{
    
}

/**
 * 组件从entity移除
 */
void Component::onRemovedFromEntity()
{
    
}


NS_CC_YHGE_END
