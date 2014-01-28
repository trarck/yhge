#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_ISOAUTOZORDERPOSITIONCOMPONENT_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_ISOAUTOZORDERPOSITIONCOMPONENT_H_

#include "cocos2d.h"
#include "ISOPositionComponent.h"

NS_CC_YHGE_BEGIN

/**
 * 通用位置组件
 * 通常以地图坐标驱动显示坐标。
 * 如果没有使用z值，可以从屏幕坐标反推地图坐标。一般不推荐这么做。
 */
class ISOAutoZOrderPositionComponent : public ISOPositionComponent
{
public:
    
    /**
     * 更新渲染坐标
     * 把地图坐标转成屏幕坐标，更新到渲染器上。
     */
    virtual void updateRendererPosition();
    
    /**
     * 更新渲染坐标
     * 直接使参数更新渲染器的坐标。参数提供的是屏幕坐标。
     * 不会把屏幕坐标反向同步到地图坐标。
     * 一般作为移动的中间过过程
     */
    virtual void updateRendererPositionDirectly(const CCPoint& pos);

};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_ISOAUTOZORDERPOSITIONCOMPONENT_H_
