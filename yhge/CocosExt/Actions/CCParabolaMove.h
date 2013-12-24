#ifndef YHGE_COCOSEXT_ACTIONS_CCPARABOLAMOVE_H_
#define YHGE_COCOSEXT_ACTIONS_CCPARABOLAMOVE_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

#define PARABOLA_GRAVITY_DEFAULT -1000.0f

NS_CC_YHGE_BEGIN

class CCParabolaMove : public CCActionInterval
{
public:
    //负的表示向下
    CCParabolaMove():m_fGravity(PARABOLA_GRAVITY_DEFAULT){}
    
    /** initializes the action */
    bool initWithDuration(float duration, const CCPoint& deltaPosition);
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse(void);
    virtual void step(float delta);
    virtual void update(float time);
    
public:
    /** creates the action */    
    static CCParabolaMove* create(float duration,const CCPoint& speed);
    
    inline void setGravity(float fGravity)
    {
        m_fGravity = fGravity;
    }
    
    inline float getGravity()
    {
        return m_fGravity;
    }
    
protected:
    CCPoint m_positionDelta;
    CCPoint m_startPosition;
    CCPoint m_previousPosition;
    
    CCPoint m_tSpeed;
    
    float m_fGravity;
};


class CCParabolaMoveTo : public CCParabolaMove
{
public:
    CCParabolaMoveTo()
    :m_fHeight(0.0f)
    ,m_bUseHight(false)
    {
        
    }
    /** initializes the action */
    bool initWithDuration(float duration, const CCPoint& position);
    
    bool initWithDuration(float duration, const CCPoint& position,float height);
        
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    
    
    void stop();
    
    inline void setHeight(float fHeight)
    {
        m_fHeight = fHeight;
    }
    
    inline float getHeight()
    {
        return m_fHeight;
    }
    
public:
    /** creates the action */
    static CCParabolaMoveTo* create(float duration,const CCPoint& position);
    static CCParabolaMoveTo* create(float duration,const CCPoint& position,float height);
    
protected:
    CCPoint m_endPosition;
    float m_fHeight;;
    bool m_bUseHight;
};


NS_CC_YHGE_END

#endif //YHGE_COCOSEXT_ACTIONS_CCPARABOLAMOVE_H_
