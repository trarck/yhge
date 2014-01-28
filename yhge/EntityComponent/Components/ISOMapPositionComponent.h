#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_ISOMapPositionComponent_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_ISOMapPositionComponent_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN

class RendererComponent;

/**
 * 基于格子的位置组件
 * 以地图坐标驱动显示坐标。
 */
class ISOMapPositionComponent : public Component 
{
public:
    
    ISOMapPositionComponent();
    
    ~ISOMapPositionComponent();
    
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
    void updateRendererPosition();
    
    /**
     * 更新渲染层级
     */
    void updateRendererZOrder();
    
    /**
     * 获取屏幕坐标
     */
    CCPoint getSceenPosition();
    
    /**
     * 设置坐标
     */
    inline void setCoordinate(float x,float y)
    {
        m_x=x;
        m_y=y;
    }
    
    /**
     * 设置坐标
     */
    inline void setCoordinate(const CCPoint& coord)
    {
        m_x=coord.x;
        m_y=coord.y;
    }
    
    
    inline void setCoordinate(float x,float y,float z)
    {
        m_x=x;
        m_y=y;
        m_z=z;
    }
    
    /**
     * 设置坐标
     */
    inline void setCoordinateAndUpdate(float x,float y)
    {
        m_x=x;
        m_y=y;
        updateRendererPosition();
    }
    
    /**
     * 设置坐标
     */
    inline void setCoordinateAndUpdate(const CCPoint& coord)
    {
        m_x=coord.x;
        m_y=coord.y;
        updateRendererPosition();
    }
    
    
    inline void setCoordinateAndUpdate(float x,float y,float z)
    {
        m_x=x;
        m_y=y;
        m_z=z;
        updateRendererPosition();
    }

    inline void setX(float x)
    {
        m_x = x;
    }
    
    inline float getX()
    {
        return m_x;
    }
    
    inline void setY(float y)
    {
        m_y = y;
    }
    
    inline float getY()
    {
        return m_y;
    }
    
    inline void setZ(float z)
    {
        m_z = z;
    }
    
    inline float getZ()
    {
        return m_z;
    }

protected:
    
    float m_x;
    float m_y;
    float m_z;
    
    RendererComponent* m_rendererComponent;
    
    bool m_dirty;
    
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_ISOMapPositionComponent_H_
