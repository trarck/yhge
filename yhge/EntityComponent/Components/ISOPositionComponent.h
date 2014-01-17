#ifndef YHGE_ENTITYCOMPONENT_COMPONENTS_ISOPositionComponent_H_
#define YHGE_ENTITYCOMPONENT_COMPONENTS_ISOPositionComponent_H_

#include "cocos2d.h"
#include "Component.h"

NS_CC_YHGE_BEGIN


class ISOPositionComponent : public Component 
{
public:
    
    ISOPositionComponent();
    
    ~ISOPositionComponent();
    
    virtual bool init();
    
    virtual bool registerMessages();
    
    virtual void cleanupMessages();
    
    /**
     * 设置坐标
     */
    inline void setCoordinate(float x,float y)
    {
        m_x=x;
        m_y=y;
    }
    
    inline void setCoordinate(float x,float y,float z)
    {
        m_x=x;
        m_y=y;
        m_z=z;
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
    
};

NS_CC_YHGE_END

#endif //YHGE_ENTITYCOMPONENT_COMPONENTS_ISOPositionComponent_H_
