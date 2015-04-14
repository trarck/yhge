#include "ISOPositionComponent.h"
#include <yhge/message.h>
#include <yhge/EntityComponent/Entity.h>
#include <yhge/Isometric/CoordinateFormulae.h>
#include "ComponentMessageDefine.h"
#include "RendererComponent.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

ISOPositionComponent::ISOPositionComponent()
:Component("ISOPositionComponent")
,_x(0.0f)
,_y(0.0f)
,_z(0.0f)
,_rendererComponent(NULL)
{

}

ISOPositionComponent::~ISOPositionComponent()
{

}

void ISOPositionComponent::setup()
{
    Component::setup();
    _rendererComponent=static_cast<RendererComponent*>(_owner->getComponent("RendererComponent"));
}

void ISOPositionComponent::cleanup()
{
    _rendererComponent=NULL;
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
    CCPoint viewPos=YHGE_ISO_COORD_TRANSLATE_WRAP(isoGameToView2F(_x, _y));
    CCNode* renderer=_rendererComponent->getRenderer();
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
    CCNode* renderer=_rendererComponent->getRenderer();
    renderer->setPosition(pos);
    renderer->setZOrder(-(int)(pos.y));
}

/**
 * 更新渲染层级
 */
void ISOPositionComponent::updateRendererZOrder()
{
    //直接使用渲染Y坐标值，作为排序值。适用于没有使用z值和没有大物体(不包含拆分成小部件的大物体)。
    CCNode* renderer=_rendererComponent->getRenderer();
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
    return _rendererComponent->getRenderer()->getPosition();
}

NS_CC_YHGE_END

