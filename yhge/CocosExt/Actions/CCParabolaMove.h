#ifndef YHGE_COCOSEXT_ACTIONS_CCPARABOLAMOVE_H_
#define YHGE_COCOSEXT_ACTIONS_CCPARABOLAMOVE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

#define PARABOLA_GRAVITY_DEFAULT -1000.0f

NS_CC_YHGE_BEGIN

class CCParabolaMove : public CCActionInterval
{
public:
    //负的表示向下
    CCParabolaMove():_fGravity(PARABOLA_GRAVITY_DEFAULT){}
    
    /** initializes the action */
    bool initWithDuration(float duration, const CCPoint& deltaPosition);
    
    virtual Ref* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse(void);
    virtual void step(float delta);
    virtual void update(float time);
    
public:
    /** creates the action */    
    static CCParabolaMove* create(float duration,const CCPoint& speed);
    
    inline void setGravity(float fGravity)
    {
        _fGravity = fGravity;
    }
    
    inline float getGravity()
    {
        return _fGravity;
    }
    
protected:
    CCPoint _positionDelta;
    CCPoint _startPosition;
    CCPoint _previousPosition;
    
    CCPoint _tSpeed;
    
    float _fGravity;
};


class CCParabolaMoveTo : public CCParabolaMove
{
public:
    CCParabolaMoveTo()
    :_fHeight(0.0f)
    ,_bUseHight(false)
    {
        
    }
    /** initializes the action */
    bool initWithDuration(float duration, const CCPoint& position);
    
    bool initWithDuration(float duration, const CCPoint& position,float height);
        
    virtual Ref* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    
    
    void stop();
    
    inline void setHeight(float fHeight)
    {
        _fHeight = fHeight;
    }
    
    inline float getHeight()
    {
        return _fHeight;
    }
    
public:
    /** creates the action */
    static CCParabolaMoveTo* create(float duration,const CCPoint& position);
    static CCParabolaMoveTo* create(float duration,const CCPoint& position,float height);
    
protected:
    CCPoint _endPosition;
    float _fHeight;;
    bool _bUseHight;
};


NS_CC_YHGE_END

#endif //YHGE_COCOSEXT_ACTIONS_CCPARABOLAMOVE_H_
