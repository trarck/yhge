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
 * 把地图坐标转成屏幕坐标，更新到渲染器上。
 */
void ISOPositionComponent::updateRendererPosition()
{
    CCPoint viewPos=isoGameToView2F(m_x, m_y);
    CCNode* renderer=m_rendererComponent->getRenderer();
    renderer->setPosition(viewPos);
    renderer->setZOrder(-(int)(viewPos.y));
}

/**
 * 更新渲染坐标
 * 直接使参数更新渲染器的坐标。参数提供的是屏幕坐标。
 * 不会把屏幕坐标反向同步到地图坐标。
 * 一般作为移动的中间过过程
 */
void ISOPositionComponent::updateRendererPositionDirectly(const CCPoint& pos)
{
    CCNode* renderer=m_rendererComponent->getRenderer();
    renderer->setPosition(pos);
    renderer->setZOrder(-(int)(pos.y));
}

/**
 * 更新渲染层级
 */
void ISOPositionComponent::updateRendererZOrder()
{
    //直接使用渲染Y坐标值，作为排序值。适用于没有使用z值和没有大物体(不包含拆分成小部件的大物体)。
    CCNode* renderer=m_rendererComponent->getRenderer();
    renderer->setZOrder(-(int)(renderer->getPositionY()));
}

/**
 * 获取渲染器的坐标
 * 对于格子移动系统，当物体在移动时，这个值和由地图坐标转成的屏幕坐标不一致。
 *    因为对于格子系统，物体在移动的开始，已经把坐标设置为要移动到的格子的坐标。
 * 对于由地图坐标驱动的系统，这个值和地坐标转换成的屏幕坐标一致。
 */
const CCPoint& ISOPositionComponent::getRendererPosition()
{
    return m_rendererComponent->getRenderer()->getPosition();
}

NS_CC_YHGE_END

