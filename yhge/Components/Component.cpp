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

}

void Component::cleanup(void)
{

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

NS_CC_YHGE_END
