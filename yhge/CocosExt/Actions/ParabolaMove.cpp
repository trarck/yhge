#include "ParabolaMove.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN


ParabolaMove* ParabolaMove::create(float duration,const Vec2& speed)
{
    ParabolaMove *pRet = new ParabolaMove();
    pRet->initWithDuration(duration, speed);
    pRet->autorelease();
    
    return pRet;
}

bool ParabolaMove::initWithDuration(float duration, const Vec2& speed)
{
    if (ActionInterval::initWithDuration(duration))
    {
        _speed= speed;
        return true;
    }
    
    return false;
}


void ParabolaMove::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget(pTarget);
    _previousPosition = _startPosition = pTarget->getPosition();
}

ActionInterval* ParabolaMove::reverse(void)
{
    return ParabolaMove::create(_duration, ccp( -_speed.x, -_speed.y));
}

void ParabolaMove::step(float delta)
{
    if (_firstTick)
    {
        _firstTick = false;
        _elapsed = 0;
    }
    else
    {
        _elapsed += delta;
    }

    this->update(delta);
}

void ParabolaMove::update(float t)
{
    if (_target)
    {
        float sx=_speed.x*_elapsed;
        float sy=_speed.y*_elapsed+0.5*_gravity*_elapsed*_elapsed;

        Vec2 newPos=ccp(_startPosition.x+sx,_startPosition.y+sy);

        _target->setPosition(newPos);
        _previousPosition = newPos;

    }
}

ParabolaMoveTo* ParabolaMoveTo::create(float duration, const Vec2 &position)
{
    ParabolaMoveTo *pRet = new ParabolaMoveTo();
    pRet->initWithDuration(duration, position);
    pRet->autorelease();
    return pRet;
}

ParabolaMoveTo* ParabolaMoveTo::create(float duration, const Vec2 &position,float height)
{
    ParabolaMoveTo *pRet = new ParabolaMoveTo();
    pRet->initWithDuration(duration, position,height);
    pRet->autorelease();
    return pRet;
}

bool ParabolaMoveTo::initWithDuration(float duration, const Vec2& position)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _endPosition= position;
        _useHight=false;
        return true;
    }
    
    return false;
}

bool ParabolaMoveTo::initWithDuration(float duration, const Vec2& position,float height)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        _endPosition= position;
        _useHight=true;
        _height=height;
        return true;
    }
    
    return false;
}


void ParabolaMoveTo::startWithTarget(Node *pTarget)
{   
    
    
    ParabolaMove::startWithTarget(pTarget);
    float sy=_endPosition.y-_startPosition.y;
    float sx=_endPosition.x-_startPosition.x;
    
    if(_useHight){
        _gravity=-2*_height/(_duration*_duration);
    }

    _speed.y=sy/_duration-0.5*_duration*_gravity;
    _speed.x= sx/_duration;

}

void ParabolaMoveTo::stop()
{
    _target->setPosition(_endPosition);
    ParabolaMove::stop();
}

NS_CC_YHGE_END