#include "ISOAutoZOrderPositionComponent.h"
#include <yhge/message.h>
#include <yhge/EntityComponent/Entity.h>
#include <yhge/Isometric/CoordinateFormulae.h>
#include "ComponentMessageDefine.h"
#include "RendererComponent.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

/**
 * 更新渲染坐标
 * 把地图坐标转成屏幕坐标，更新到渲染器上。
 */
void ISOAutoZOrderPositionComponent::updateRendererPosition()
{
    CCPoint viewPos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(m_x, m_y));
    CCNode* renderer=m_rendererComponent->getRenderer();
    renderer->setPosition(viewPos);
    //发送位置改变消息
    this->getMessageManager()->dispatchMessage(MSG_POSITION_CHANGE, this, m_owner);
}

/**
 * 更新渲染坐标
 * 直接使参数更新渲染器的坐标。参数提供的是屏幕坐标。
 * 不会把屏幕坐标反向同步到地图坐标。
 * 一般作为移动的中间过过程
 */
void ISOAutoZOrderPositionComponent::updateRendererPositionDirectly(const CCPoint& pos)
{
    CCNode* renderer=m_rendererComponent->getRenderer();
    renderer->setPosition(pos);
//    //发送位置改变消息
//    this->getMessageManager()->dispatchMessage(MSG_POSITION_CHANGE, this, m_owner);
}

NS_CC_YHGE_END

