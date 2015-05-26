#ifndef YHGE_COCOSEXT_ACTIONS_CCPARABOLAMOVE_H_
#define YHGE_COCOSEXT_ACTIONS_CCPARABOLAMOVE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

#define PARABOLA_GRAVITY_DEFAULT -1000.0f

NS_CC_YHGE_BEGIN

class ParabolaMove : public ActionInterval
{
public:
    //负的表示向下
    ParabolaMove():_gravity(PARABOLA_GRAVITY_DEFAULT){}
    
    /** initializes the action */
    bool initWithDuration(float duration, const Vec2& deltaPosition);
    
    virtual void startWithTarget(Node *pTarget);
    virtual ActionInterval* reverse(void);
    virtual void step(float delta);
    virtual void update(float time);
    
public:
    /** creates the action */    
    static ParabolaMove* create(float duration,const Vec2& speed);
    
    inline void setGravity(float gravity)
    {
        _gravity = gravity;
    }
    
    inline float getGravity()
    {
        return _gravity;
    }
    
protected:
    Vec2 _positionDelta;
    Vec2 _startPosition;
    Vec2 _previousPosition;
    
    Vec2 _speed;
    
    float _gravity;
};


class ParabolaMoveTo : public ParabolaMove
{
public:
    ParabolaMoveTo()
    :_height(0.0f)
    ,_useHight(false)
    {
        
    }
    /** initializes the action */
    bool initWithDuration(float duration, const Vec2& position);
    
    bool initWithDuration(float duration, const Vec2& position,float height);
        
    virtual void startWithTarget(Node *pTarget);
    
    
    void stop();
    
    inline void setHeight(float height)
    {
        _height = height;
    }
    
    inline float getHeight()
    {
        return _height;
    }
    
public:
    /** creates the action */
    static ParabolaMoveTo* create(float duration,const Vec2& position);
    static ParabolaMoveTo* create(float duration,const Vec2& position,float height);
    
protected:
    Vec2 _endPosition;
    float _height;;
    bool _useHight;
};


NS_CC_YHGE_END

#endif //YHGE_COCOSEXT_ACTIONS_CCPARABOLAMOVE_H_
