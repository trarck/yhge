#include "ISOPositionComponent.h"
#include <yhge/message.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

ISOPositionComponent::ISOPositionComponent()
:m_x(0.0f)
,m_y(0.0f)
,m_z(0.0f)
{
    CCLOG("ISOPositionComponent create");
    m_name="ISOPositionComponent";
}

ISOPositionComponent::~ISOPositionComponent()
{
    CCLOG("ISOPositionComponent destroy");
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

