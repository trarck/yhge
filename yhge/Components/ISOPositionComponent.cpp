#include "ISOPositionComponent.h"
#include <yhge/message.h>
#include "ComponentMessageDefine.h"
#include "Entity.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

ISOPositionComponent::ISOPositionComponent()
:m_renderer(NULL)
{
    CCLOG("ISOPositionComponent create");
    m_name="ISOPositionComponent";
}

ISOPositionComponent::~ISOPositionComponent()
{
    CCLOG("ISOPositionComponent destroy");
    CC_SAFE_RELEASE_NULL(m_renderer);
}

bool ISOPositionComponent::init()
{
    CCLOG("ISOPositionComponent init");
    return true;
}

bool ISOPositionComponent::registerMessages()
{
    CCLOG("ISOPositionComponent::registerMessages");
    
    if(Component::registerMessages()){
        return true;
    }
    return false;
}

void ISOPositionComponent::cleanupMessages()
{
	CCLOG("ISOPositionComponent::cleanupMessages");

    Component::cleanupMessages();
}

NS_CC_YHGE_END

