#include "ISOPositionComponent.h"
#include <yhge/message.h>
#include <yhge/EntityComponent/Entity.h>
#include <yhge/Isometric/ISOCoordinate.h>
#include "ComponentMessageDefine.h"
#include "RendererComponent.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

ISOPositionComponent::ISOPositionComponent()
:Component("ISOPositionComponent")
,m_x(0.0f)
,m_y(0.0f)
,m_z(0.0f)
,m_rendererComponent(NULL)
{

}

ISOPositionComponent::~ISOPositionComponent()
{

}

void ISOPositionComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void ISOPositionComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool ISOPositionComponent::registerMessages()
{
    if(Component::registerMessages()){
        return true;
    }
    return false;
}

void ISOPositionComponent::cleanupMessages()
{
    Component::cleanupMessages();
}

/**
 * 更新渲染坐标
 */
void ISOPositionComponent::updateRendererPosition()
{
    CCPoint viewPos=isoGameToView2F(m_x, m_y);
    m_rendererComponent->getRenderer()->setPosition(viewPos);
}

NS_CC_YHGE_END

