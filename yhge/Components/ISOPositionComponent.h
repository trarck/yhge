#ifndef YHGE_COMPONENTS_ISOPositionComponent_H_
#define YHGE_COMPONENTS_ISOPositionComponent_H_

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
        
    void setMx(float mx)
    {
        m_mx = mx;
    }

    float getMx()
    {
        return m_mx;
    }

    void setMy(float my)
    {
        m_my = my;
    }

    float getMy()
    {
        return m_my;
    }

    void setMz(float mz)
    {
        m_mz = mz;
    }

    float getMz()
    {
        return m_mz;
    }

protected:
    
    float m_mx;
    float m_my;
    float m_mz;
    
};

NS_CC_YHGE_END

#endif //YHGE_COMPONENTS_ISOPositionComponent_H_
