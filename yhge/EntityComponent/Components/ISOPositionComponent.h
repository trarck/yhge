#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_ISOPositionComponent_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_ISOPositionComponent_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN

class RendererComponent;

/**
 * 通用位置组件
 * 通常以地图坐标驱动显示坐标。
 * 如果没有使用z值，可以从屏幕坐标反推地图坐标。一般不推荐这么做。
 */
class ISOPositionComponent : public Component 
{
public:
    
    ISOPositionComponent();
    
    ~ISOPositionComponent();
    
    /**
     * 设置
     */
    virtual void setup();
    
    /**
     * 消除
     */
    virtual void cleanup();
    
    virtual bool registerMessages();
    
    virtual void cleanupMessages();
    
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
    
    /**
     * 更新渲染层级
     */
    void updateRendererZOrder();
    
    /**
     * 获取渲染器的坐标
     * 对于格子移动系统，当物体在移动时，这个值和由地图坐标转成的屏幕坐标不一致。
     *    因为对于格子系统，物体在移动的开始，已经把坐标设置为要移动到的格子的坐标。
     * 对于由地图坐标驱动的系统，这个值和地坐标转换成的屏幕坐标一致。
     */
    const CCPoint& getRendererPosition();
    
    /**
     * 设置坐标
     */
    inline void setCoordinate(float x,float y)
    {
        _x=x;
        _y=y;
    }
    
    /**
     * 设置坐标
     */
    inline void setCoordinate(const CCPoint& coord)
    {
        _x=coord.x;
        _y=coord.y;
    }
    
    
    inline void setCoordinate(float x,float y,float z)
    {
        _x=x;
        _y=y;
        _z=z;
    }
    
    /**
     * 设置坐标
     */
    inline void setCoordinateAndUpdate(float x,float y)
    {
        _x=x;
        _y=y;
        updateRendererPosition();
    }
    
    /**
     * 设置坐标
     */
    inline void setCoordinateAndUpdate(const CCPoint& coord)
    {
        _x=coord.x;
        _y=coord.y;
        updateRendererPosition();
    }
    
    
    inline void setCoordinateAndUpdate(float x,float y,float z)
    {
        _x=x;
        _y=y;
        _z=z;
        updateRendererPosition();
    }

    inline void setX(float x)
    {
        _x = x;
    }
    
    inline float getX()
    {
        return _x;
    }
    
    inline void setY(float y)
    {
        _y = y;
    }
    
    inline float getY()
    {
        return _y;
    }
    
    inline void setZ(float z)
    {
        _z = z;
    }
    
    inline float getZ()
    {
        return _z;
    }

protected:
    
    float _x;
    float _y;
    float _z;
    
    RendererComponent* _rendererComponent;
    
    bool _dirty;
    
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_ISOPositionComponent_H_
