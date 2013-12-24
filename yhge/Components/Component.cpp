#include "Component.h"
#include <yhge/Message/MessageManager.h>

NS_CC_YHGE_BEGIN

Component::Component()
:m_pOwner(NULL)
,m_sName("")
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
