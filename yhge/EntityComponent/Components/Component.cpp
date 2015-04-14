#include "Component.h"
#include <yhge/Base/Log.h>
#include <yhge/Message/MessageManager.h>

NS_CC_YHGE_BEGIN

Component::Component()
:_name("")
,_owner(NULL)
,_type(0)
{
    YHDEBUG("Component[0x%lx] create",(unsigned long)this);
}

Component::Component(const std::string& name)
:_name(name)
,_owner(NULL)
{
    YHDEBUG("Component[0x%lx](%s) create",(unsigned long)this,_name.c_str());
}

Component::~Component()
{
    YHDEBUG("Component[0x%lx](%s) destroy",(unsigned long)this,_name.c_str());
}

bool Component::init(void)
{
    YHDEBUG("Component[0x%lx](%s) init",(unsigned long)this,_name.c_str());
    return true;
}

void Component::setup(void)
{
    YHDEBUG("Component[0x%lx](%s)::setup",(unsigned long)this,_name.c_str());
    this->registerMessages();
}

void Component::cleanup(void)
{
    YHDEBUG("Component[0x%lx](%s)::cleanup",(unsigned long)this,_name.c_str());
    this->cleanupMessages();
}

bool Component::registerMessages()
{
    YHDEBUG("Component[0x%lx](%s)::registerMessages",(unsigned long)this,_name.c_str());
    
    return true;
}

void Component::cleanupMessages()
{
    YHDEBUG("Component[0x%lx](%s)::cleanupMessages",(unsigned long)this,_name.c_str());
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

void Component::update(float delta)
{
    //do nothing
}


NS_CC_YHGE_END
