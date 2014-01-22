#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_ISOPositionComponent_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_ISOPositionComponent_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN

class RendererComponent;

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
     */
    void updateRendererPosition();
    
    /**
     * 更新渲染层级
     */
    void updateRendererZOrder();
    
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

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_ISOPositionComponent_H_
