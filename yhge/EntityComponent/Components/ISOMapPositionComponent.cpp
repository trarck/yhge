#include "ISOMapPositionComponent.h"
#include <yhge/message.h>
#include <yhge/EntityComponent/Entity.h>
#include <yhge/Isometric/CoordinateFormulae.h>
#include "ComponentMessageDefine.h"
#include "RendererComponent.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

ISOMapPositionComponent::ISOMapPositionComponent()
:Component("ISOMapPositionComponent")
,m_x(0.0f)
,m_y(0.0f)
,m_z(0.0f)
,m_rendererComponent(NULL)
{

}

ISOMapPositionComponent::~ISOMapPositionComponent()
{

}

void ISOMapPositionComponent::setup()
{
    Component::setup();
    m_rendererComponent=static_cast<RendererComponent*>(m_owner->getComponent("RendererComponent"));
}

void ISOMapPositionComponent::cleanup()
{
    m_rendererComponent=NULL;
    Component::cleanup();
}

bool ISOMapPositionComponent::registerMessages()
{
    if(Component::registerMessages()){
        return true;
    }
    return false;
}

void ISOMapPositionComponent::cleanupMessages()
{
    Component::cleanupMessages();
}

/**
 * 更新渲染坐标
 * 把地图坐标转成屏幕坐标，更新到渲染器上。
 */
void ISOMapPositionComponent::updateRendererPosition()
{
    CCPoint viewPos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(m_x, m_y));
    CCNode* renderer=m_rendererComponent->getRenderer();
    renderer->setPosition(viewPos);
    renderer->setZOrder(-(int)(viewPos.y));
}

/**
 * 更新渲染层级
 */
void ISOMapPositionComponent::updateRendererZOrder()
{
    //直接使用渲染Y坐标值，作为排序值。适用于没有使用z值和没有大物体(不包含拆分成小部件的大物体)。
    CCNode* renderer=m_rendererComponent->getRenderer();
    renderer->setZOrder(-(int)(renderer->getPositionY()));
}

/**
 * 获取渲屏幕坐标
 */
CCPoint ISOMapPositionComponent::getSceenPosition()
{
    return YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(m_x, m_y));
}

NS_CC_YHGE_END

