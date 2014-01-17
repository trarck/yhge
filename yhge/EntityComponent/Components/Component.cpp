#include "Component.h"
#include <yhge/Message/MessageManager.h>

NS_CC_YHGE_BEGIN

Component::Component()
:m_name("")
,m_owner(NULL)
{
    CCLOG("Component create");
}

Component::~Component()
{
    CCLOG("Component destroy");
}

bool Component::init(void)
{
    CCLOG("Component init");
    return true;
}

void Component::setup(void)
{
    this->registerMessages();
}

void Component::cleanup(void)
{
    this->cleanupMessages();
}

bool Component::registerMessages()
{
    CCLOG("Component::registerMessages");
    
    return true;
}

void Component::cleanupMessages()
{
    CCLOG("Component::cleanupMessages");
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
